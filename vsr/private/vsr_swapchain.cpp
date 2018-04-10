#include "vsr_common.h"

#ifdef VK_USE_PLATFORM_WIN32_KHR
#include <dxgi.h>
#include <d3d11.h>
#endif

#include "vsr_swapchain.h"

#ifdef VK_USE_PLATFORM_WIN32_KHR
VkResult VkSwapchainKHR_T::Init_Win32(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo)
{
	_pFactory = nullptr;
	_pAdapter = nullptr;
	_pd3dDevice = nullptr;

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

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	//pCreateInfo->
	//DXGI_FORMAT dxFormat = DX11RenderEngine::GetPixelFormat(GConfig->pRenderConfig->ColorFormat);
	//while (GConfig->pRenderConfig->MultiSampleCount > 1)
	//{
	//	_pd3dDevice->CheckMultisampleQualityLevels(dxFormat, GConfig->pRenderConfig->MultiSampleCount, &GConfig->pRenderConfig->MultiSampleQuality);
	//	if (GConfig->pRenderConfig->MultiSampleQuality == 0) // invalid
	//	{
	//		GConfig->pRenderConfig->MultiSampleCount--;
	//	}
	//	else
	//	{
	//		GConfig->pRenderConfig->MultiSampleQuality--;
	//		break;
	//	}
	//}

	//sd.BufferCount = 1;
	//sd.BufferDesc.Width = GConfig->pRenderConfig->SizeX;
	//sd.BufferDesc.Height = GConfig->pRenderConfig->SizeY;
	//sd.BufferDesc.Format = dxFormat;
	//sd.BufferDesc.RefreshRate.Numerator = 60;
	//sd.BufferDesc.RefreshRate.Denominator = 1;
	//sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//sd.OutputWindow = (HWND)hWnd;
	//sd.SampleDesc.Count = GConfig->pRenderConfig->MultiSampleCount;
	//sd.SampleDesc.Quality = GConfig->pRenderConfig->MultiSampleQuality;
	//sd.Windowed = TRUE;

	//IDXGISwapChain*  pSwapChain;
	//hr = _pDXGIFactory->CreateSwapChain(_pd3dDevice.get(), &sd, &pSwapChain);
	//BOOST_ASSERT(SUCCEEDED(hr));
	//_pSwapChain = MakeComPtr<IDXGISwapChain>(pSwapChain);

	//hr = _pDXGIFactory->MakeWindowAssociation((HWND)hWnd, DXGI_MWA_NO_WINDOW_CHANGES);
	//BOOST_ASSERT(SUCCEEDED(hr));

	//// Create a render target view
	//ID3D11Texture2D* pBackBuffer = NULL;
	//hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	//BOOST_ASSERT(SUCCEEDED(hr));
	//DX11RenderTexture2DPtr BackBufferTex = DX11RenderTexture2D::Create(GConfig->pRenderConfig->ColorFormat, sd.BufferDesc.Width, sd.BufferDesc.Height, SV_RenderTarget | SV_ShaderResource, false,
	//	GConfig->pRenderConfig->MultiSampleCount, GConfig->pRenderConfig->MultiSampleQuality, MakeComPtr<ID3D11Texture2D>(pBackBuffer));

	//SurfaceViewPtr rtView = GEngine->RenderResourceMgr->CreateSurfaceView(SV_RenderTarget, BackBufferTex, GConfig->pRenderConfig->ColorFormat);

	return VK_SUCCESS;
}
#endif

VkResult VkSwapchainKHR_T::Init(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo)
{
#ifdef VK_USE_PLATFORM_WIN32_KHR
	return Init_Win32(device, pCreateInfo);
#endif
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(
	VkDevice                                    device,
	const VkSwapchainCreateInfoKHR*             pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSwapchainKHR*                             pSwapchain)
{
	VkSwapchainKHR_T *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = (VkSwapchainKHR_T*)pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkSwapchainKHR_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
	}
	else
	{
		pMem = (VkSwapchainKHR_T*)std::malloc(sizeof(VkSwapchainKHR_T));
	}

	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	pMem = new(pMem) VkSwapchainKHR_T;

	VkResult res = pMem->Init(device, pCreateInfo);
	if (res != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(device,pMem, pAllocator);
		return res;
	}

	*pSwapchain = pMem;

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	const VkAllocationCallbacks*                pAllocator)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint32_t*                                   pSwapchainImageCount,
	VkImage*                                    pSwapchainImages)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint64_t                                    timeout,
	VkSemaphore                                 semaphore,
	VkFence                                     fence,
	uint32_t*                                   pImageIndex)
{
	return VK_SUCCESS;
}


VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(
	VkQueue                                     queue,
	const VkPresentInfoKHR*                     pPresentInfo)
{
	return VK_SUCCESS;
}