#include "vsr_define.h"
#include "vsr_instance.h"


#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include "../public/vsr_surface.h"
#include "vsr_surface.h"

void vkDestroySurfaceKHR(
	VkInstance                                  instance,
	VkSurfaceKHR                                surface,
	const VkAllocationCallbacks*                pAllocator)
{
	if (pAllocator != nullptr)
	{
		pAllocator->pfnFree(pAllocator->pUserData, (void*)surface);
	}
	else
	{
		std::free((void*)surface);
	}
}


VkResult vkGetPhysicalDeviceSurfaceSupportKHR(
	VkPhysicalDevice                            physicalDevice,
	uint32_t                                    queueFamilyIndex,
	VkSurfaceKHR                                surface,
	VkBool32*                                   pSupported)
{
	return VK_SUCCESS;
}

VkResult  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities)
{
	return VK_SUCCESS;
}

VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pSurfaceFormatCount,
	VkSurfaceFormatKHR*                         pSurfaceFormats)
{
	return VK_SUCCESS;
}

VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pPresentModeCount,
	VkPresentModeKHR*                           pPresentModes)
{
	return VK_SUCCESS;
}

#ifdef VK_USE_PLATFORM_WIN32_KHR

WINSurface_T::WINSurface_T(HINSTANCE hinstance, HWND hwnd)
	:_hinstance(hinstance),_hwnd(hwnd)
{

}

VkResult vkCreateWin32SurfaceKHR(
	VkInstance                                  instance,
	const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSurfaceKHR*                               pSurface)
{
	void *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(WINSurface_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE);
	}
	else
	{
		pMem = std::malloc(sizeof(WINSurface_T));
	}

	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	WINSurface_T *pWS = new (pMem) WINSurface_T(pCreateInfo->hinstance,pCreateInfo->hwnd);
	
	*pSurface = (VkSurfaceKHR)pMem;

	return VK_SUCCESS;
}
 

//VkBool32 vkGetPhysicalDeviceWin32PresentationSupportKHR(
//	VkPhysicalDevice                            physicalDevice,
//	uint32_t                                    queueFamilyIndex)
//{
//	return VK_TRUE;
//}



#endif