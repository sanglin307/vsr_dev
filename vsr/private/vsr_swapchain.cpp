#include "vsr_common.h"

#ifdef VK_USE_PLATFORM_WIN32_KHR
#include <dxgi.h>
#include <d3d11.h>
#endif

#include "vsr_image.h"
#include "vsr_surface.h"
#include "vsr_swapchain.h"
#include "vsr_sync.h"
#include "vsr_device.h"

#ifdef VK_USE_PLATFORM_WIN32_KHR

DXGI_FORMAT ConvertToDXFormat(VkFormat format)
{
	if (format == VK_FORMAT_B8G8R8A8_UNORM)
		return DXGI_FORMAT_B8G8R8A8_UNORM;
	else if (format == VK_FORMAT_B8G8R8A8_SRGB)
		return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	else if (format == VK_FORMAT_R8G8B8A8_UNORM)
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (format == VK_FORMAT_R8G8B8A8_SRGB)
		return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	else
		assert(0);

	return DXGI_FORMAT_UNKNOWN;
}

void VkSwapchainKHR_T::Exit_Win32()
{
	if (_pImmediateContext != nullptr)
	{
		_pImmediateContext->ClearState();
		_pImmediateContext->Release();
		_pImmediateContext = nullptr;
	}

	if (_pSwapChain != nullptr)
	{
		_pSwapChain->Release();
		_pSwapChain = nullptr;
	}

	if (_pd3dDevice != nullptr)
	{
		_pd3dDevice->Release();
		_pd3dDevice = nullptr;
	}
}

VkResult VkSwapchainKHR_T::Init_Win32(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo)
{
	_pFactory = nullptr;
	_pAdapter = nullptr;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pBackBuffer = nullptr;

	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&_pFactory));
	assert(SUCCEEDED(hr));
	if (FAILED(hr))
		return VK_ERROR_SURFACE_LOST_KHR;

	UINT i = 0;
	while (_pFactory->EnumAdapters(i, &_pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		break;
	}

	UINT DeviceCreationFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_UNKNOWN;

#ifdef _DEBUG
	DeviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE(FeatureLevels);

	hr = D3D11CreateDevice(_pAdapter, DriverType, NULL, DeviceCreationFlags, FeatureLevels, numFeatureLevels, D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
	assert(SUCCEEDED(hr));

	if (FAILED(hr))
		return VK_ERROR_SURFACE_LOST_KHR;

	WINSurface_T* pSurface = (WINSurface_T*)(pCreateInfo->surface);
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	DXGI_FORMAT dxFormat = ConvertToDXFormat(pCreateInfo->imageFormat);
	sd.BufferCount = 1;
	sd.BufferDesc.Width = pCreateInfo->imageExtent.width;
	sd.BufferDesc.Height = pCreateInfo->imageExtent.height;
	sd.BufferDesc.Format = dxFormat;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT ;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.OutputWindow = pSurface->_hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	
	hr = _pFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain);
	assert(SUCCEEDED(hr));
	if (FAILED(hr))
		return VK_ERROR_SURFACE_LOST_KHR;
	 
	hr = _pFactory->MakeWindowAssociation(pSurface->_hwnd, DXGI_MWA_NO_WINDOW_CHANGES);
	assert(SUCCEEDED(hr));

 
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_pBackBuffer);
	assert(SUCCEEDED(hr));

	return VK_SUCCESS;
}
#endif

VkAllocationCallbacks *MemoryAlloc<VkSwapchainKHR_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;

VkResult VkSwapchainKHR_T::GetSwapchainImagesKHR(uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
	*pSwapchainImageCount = (uint32_t)_vecImages.size();
	if (pSwapchainImages != nullptr)
	{
		for (uint32_t i = 0; i < _vecImages.size(); i++)
		{
			pSwapchainImages[i] = _vecImages[i];
		}
	}

	return VK_SUCCESS;
}

VkResult VkSwapchainKHR_T::AcquireNextImageKHR(uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
	//todo
	*pImageIndex = _presenting + 1;
	if (*pImageIndex >= _vecImages.size())
	{
		*pImageIndex = 0;
	}

	if (semaphore != nullptr)
		semaphore->Signal(true);

	if (fence != nullptr)
		fence->Signal(true);

	return VK_SUCCESS;
}

VkResult VkSwapchainKHR_T::Init(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo)
{
#ifdef VK_USE_PLATFORM_WIN32_KHR
	VkResult res = Init_Win32(device, pCreateInfo);
	if (res != VK_SUCCESS)
		return res;
#endif
	for (uint32_t i = 0; i < pCreateInfo->minImageCount; i++)
	{
		VkExtent3D extent = { pCreateInfo->imageExtent.width,pCreateInfo->imageExtent.height,0 };
		VkImage image = new (_pAllocator) VkImage_T(VK_IMAGE_TYPE_2D,pCreateInfo->imageFormat,extent,1,
			pCreateInfo->imageArrayLayers, VK_IMAGE_TILING_OPTIMAL,pCreateInfo->imageUsage,pCreateInfo->imageSharingMode,pCreateInfo->queueFamilyIndexCount,
			pCreateInfo->pQueueFamilyIndices, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
		_vecImages.push_back(image);
		_presenting = -1;
	}
	return VK_SUCCESS;
}

VkSwapchainKHR_T::~VkSwapchainKHR_T()
{
	for (uint32_t i = 0; i < _vecImages.size(); i++)
	{
		delete _vecImages[i];
	}
	_vecImages.clear();

#ifdef VK_USE_PLATFORM_WIN32_KHR
	 Exit_Win32();
#endif
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(
	VkDevice                                    device,
	const VkSwapchainCreateInfoKHR*             pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSwapchainKHR*                             pSwapchain)
{
	try
	{
		*pSwapchain = new(pAllocator) VkSwapchainKHR_T;
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	 
	VkResult res = (*pSwapchain)->Init(device, pCreateInfo);
	if (res != VK_SUCCESS)
	{
		delete *pSwapchain;
		return res;
	}

	device->Registe(*pSwapchain);
 
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(swapchain);
	delete swapchain;
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint32_t*                                   pSwapchainImageCount,
	VkImage*                                    pSwapchainImages)
{
	return swapchain->GetSwapchainImagesKHR(pSwapchainImageCount, pSwapchainImages);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint64_t                                    timeout,
	VkSemaphore                                 semaphore,
	VkFence                                     fence,
	uint32_t*                                   pImageIndex)
{
	return swapchain->AcquireNextImageKHR(timeout, semaphore, fence, pImageIndex);
}


