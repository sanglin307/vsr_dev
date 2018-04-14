#include "vsr_common.h"
#include "vsr_surface.h"

VkSurfaceKHR_T::VkSurfaceKHR_T()
{
	VkSurfaceFormatKHR sf0 = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
	_format.push_back(sf0);
	//VkSurfaceFormatKHR sf1 = { VK_FORMAT_B8G8R8A8_SRGB, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pSurfaceFormatCount,
	VkSurfaceFormatKHR*                         pSurfaceFormats)
{
	*pSurfaceFormatCount = (uint32_t)surface->_format.size();
	if (pSurfaceFormats == nullptr)
		return VK_SUCCESS;

	for (size_t i = 0; i < surface->_format.size(); i++)
	{
		pSurfaceFormats[i] = surface->_format[i];
	}

	return VK_SUCCESS;
}

void vkDestroySurfaceKHR(
	VkInstance                                  instance,
	VkSurfaceKHR                                surface,
	const VkAllocationCallbacks*                pAllocator)
{
	delete surface;
}


VkResult vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities)
{
	*pSurfaceCapabilities = surface->_capability;
	return VK_SUCCESS;
}



VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pPresentModeCount,
	VkPresentModeKHR*                           pPresentModes)
{
	*pPresentModeCount = sizeof(surface->_presentModes) / sizeof(VkPresentModeKHR);
	if (pPresentModes == nullptr)
		return VK_SUCCESS;

	for (size_t i = 0; i < sizeof(surface->_presentModes) / sizeof(VkPresentModeKHR); i++)
	{
		pPresentModes[i] = surface->_presentModes[i];
	}

	return VK_SUCCESS;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR

VkAllocationCallbacks *MemoryAlloc<WINSurface_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE>::_pAllocator = nullptr;
WINSurface_T::WINSurface_T(HINSTANCE hinstance, HWND hwnd)
	:_hinstance(hinstance),_hwnd(hwnd)
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	_capability.currentExtent = { uint32_t(rect.right - rect.left), uint32_t(rect.bottom - rect.top) };
}

VkResult vkCreateWin32SurfaceKHR(
	VkInstance                                  instance,
	const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSurfaceKHR*                               pSurface)
{
	try
	{
		*pSurface = new(pAllocator) WINSurface_T(pCreateInfo->hinstance, pCreateInfo->hwnd);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}
 

VkBool32 vkGetPhysicalDeviceWin32PresentationSupportKHR(
	VkPhysicalDevice                            physicalDevice,
	uint32_t                                    queueFamilyIndex)
{
	return VK_TRUE;
}



#endif