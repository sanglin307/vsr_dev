#pragma once
#include "vsr_define.h"
#include "vsr_physicaldevice.h"

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSurfaceKHR)

#define VK_KHR_SURFACE_EXTENSION_NAME     "VK_KHR_surface"

typedef struct VkSurfaceCapabilitiesKHR {
	uint32_t                         minImageCount;
	uint32_t                         maxImageCount;
	VkExtent2D                       currentExtent;
	VkExtent2D                       minImageExtent;
	VkExtent2D                       maxImageExtent;
	uint32_t                         maxImageArrayLayers;
	VkSurfaceTransformFlagsKHR       supportedTransforms;
	VkSurfaceTransformFlagBitsKHR    currentTransform;
	VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
	VkImageUsageFlags                supportedUsageFlags;
} VkSurfaceCapabilitiesKHR;

typedef struct VkSurfaceFormatKHR {
	VkFormat           format;
	VkColorSpaceKHR    colorSpace;
} VkSurfaceFormatKHR;

void vkDestroySurfaceKHR(
	VkInstance                                  instance,
	VkSurfaceKHR                                surface,
	const VkAllocationCallbacks*                pAllocator);

VkResult vkGetPhysicalDeviceSurfaceSupportKHR(
	VkPhysicalDevice                            physicalDevice,
	uint32_t                                    queueFamilyIndex,
	VkSurfaceKHR                                surface,
	VkBool32*                                   pSupported);

VkResult  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities);

VkResult vkGetPhysicalDeviceSurfaceFormatsKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pSurfaceFormatCount,
	VkSurfaceFormatKHR*                         pSurfaceFormats);

VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pPresentModeCount,
	VkPresentModeKHR*                           pPresentModes);

//windows platform
#ifdef VK_USE_PLATFORM_WIN32_KHR
#define VK_KHR_win32_surface 1
#include <windows.h>

#define VK_KHR_WIN32_SURFACE_SPEC_VERSION 6
#define VK_KHR_WIN32_SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

typedef VkFlags VkWin32SurfaceCreateFlagsKHR;

typedef struct VkWin32SurfaceCreateInfoKHR {
	VkStructureType                 sType;
	const void*                     pNext;
	VkWin32SurfaceCreateFlagsKHR    flags;
	HINSTANCE                       hinstance;
	HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;

VkResult vkCreateWin32SurfaceKHR(
	VkInstance                                  instance,
	const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSurfaceKHR*                               pSurface);


VkBool32 vkGetPhysicalDeviceWin32PresentationSupportKHR(
	VkPhysicalDevice                            physicalDevice,
	uint32_t                                    queueFamilyIndex);

#endif /* VK_USE_PLATFORM_WIN32_KHR */

