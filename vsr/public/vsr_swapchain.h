#pragma once

#include "vsr_define.h"
#include "vsr_device.h"
#include "vsr_queue.h"
#include "vsr_surface.h"
#include "vsr_semaphore.h"
#include "vsr_fence.h"
#include "vsr_image.h"


VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSwapchainKHR)

typedef enum VkSwapchainCreateFlagBitsKHR {
	VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR = 0x00000001,
	VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR = 0x00000002,
	VK_SWAPCHAIN_CREATE_FLAG_BITS_MAX_ENUM_KHR = 0x7FFFFFFF
} VkSwapchainCreateFlagBitsKHR;
typedef VkFlags VkSwapchainCreateFlagsKHR;


typedef struct VkSwapchainCreateInfoKHR {
	VkStructureType                  sType;
	const void*                      pNext;
	VkSwapchainCreateFlagsKHR        flags;
	VkSurfaceKHR                     surface;
	uint32_t                         minImageCount;
	VkFormat                         imageFormat;
	VkColorSpaceKHR                  imageColorSpace;
	VkExtent2D                       imageExtent;
	uint32_t                         imageArrayLayers;
	VkImageUsageFlags                imageUsage;
	VkSharingMode                    imageSharingMode;
	uint32_t                         queueFamilyIndexCount;
	const uint32_t*                  pQueueFamilyIndices;
	VkSurfaceTransformFlagBitsKHR    preTransform;
	VkCompositeAlphaFlagBitsKHR      compositeAlpha;
	VkPresentModeKHR                 presentMode;
	VkBool32                         clipped;
	VkSwapchainKHR                   oldSwapchain;
} VkSwapchainCreateInfoKHR;

typedef struct VkPresentInfoKHR {
	VkStructureType          sType;
	const void*              pNext;
	uint32_t                 waitSemaphoreCount;
	const VkSemaphore*       pWaitSemaphores;
	uint32_t                 swapchainCount;
	const VkSwapchainKHR*    pSwapchains;
	const uint32_t*          pImageIndices;
	VkResult*                pResults;
} VkPresentInfoKHR;

typedef VkFlags VkDeviceGroupPresentModeFlagsKHR;

typedef struct VkDeviceGroupPresentCapabilitiesKHR {
	VkStructureType                     sType;
	const void*                         pNext;
	uint32_t                            presentMask[VK_MAX_DEVICE_GROUP_SIZE];
	VkDeviceGroupPresentModeFlagsKHR    modes;
} VkDeviceGroupPresentCapabilitiesKHR;


typedef struct VkAcquireNextImageInfoKHR {
	VkStructureType    sType;
	const void*        pNext;
	VkSwapchainKHR     swapchain;
	uint64_t           timeout;
	VkSemaphore        semaphore;
	VkFence            fence;
	uint32_t           deviceMask;
} VkAcquireNextImageInfoKHR;


typedef VkResult(VKAPI_PTR *PFN_vkCreateSwapchainKHR)(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain);
typedef void (VKAPI_PTR *PFN_vkDestroySwapchainKHR)(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator);
typedef VkResult(VKAPI_PTR *PFN_vkGetSwapchainImagesKHR)(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages);
typedef VkResult(VKAPI_PTR *PFN_vkAcquireNextImageKHR)(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex);
typedef VkResult(VKAPI_PTR *PFN_vkQueuePresentKHR)(VkQueue queue, const VkPresentInfoKHR* pPresentInfo);
typedef VkResult(VKAPI_PTR *PFN_vkGetDeviceGroupPresentCapabilitiesKHR)(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities);
typedef VkResult(VKAPI_PTR *PFN_vkGetDeviceGroupSurfacePresentModesKHR)(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes);
typedef VkResult(VKAPI_PTR *PFN_vkGetPhysicalDevicePresentRectanglesKHR)(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects);
typedef VkResult(VKAPI_PTR *PFN_vkAcquireNextImage2KHR)(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(
	VkDevice                                    device,
	const VkSwapchainCreateInfoKHR*             pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSwapchainKHR*                             pSwapchain);

VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	const VkAllocationCallbacks*                pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint32_t*                                   pSwapchainImageCount,
	VkImage*                                    pSwapchainImages);

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint64_t                                    timeout,
	VkSemaphore                                 semaphore,
	VkFence                                     fence,
	uint32_t*                                   pImageIndex);

VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(
	VkQueue                                     queue,
	const VkPresentInfoKHR*                     pPresentInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupPresentCapabilitiesKHR(
	VkDevice                                    device,
	VkDeviceGroupPresentCapabilitiesKHR*        pDeviceGroupPresentCapabilities);

VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupSurfacePresentModesKHR(
	VkDevice                                    device,
	VkSurfaceKHR                                surface,
	VkDeviceGroupPresentModeFlagsKHR*           pModes);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDevicePresentRectanglesKHR(
	VkPhysicalDevice                            physicalDevice,
	VkSurfaceKHR                                surface,
	uint32_t*                                   pRectCount,
	VkRect2D*                                   pRects);

VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImage2KHR(
	VkDevice                                    device,
	const VkAcquireNextImageInfoKHR*            pAcquireInfo,
	uint32_t*                                   pImageIndex);
#endif


#define VK_GOOGLE_display_timing 1
#define VK_GOOGLE_DISPLAY_TIMING_SPEC_VERSION 1
#define VK_GOOGLE_DISPLAY_TIMING_EXTENSION_NAME "VK_GOOGLE_display_timing"

typedef struct VkRefreshCycleDurationGOOGLE {
	uint64_t    refreshDuration;
} VkRefreshCycleDurationGOOGLE;

typedef struct VkPastPresentationTimingGOOGLE {
	uint32_t    presentID;
	uint64_t    desiredPresentTime;
	uint64_t    actualPresentTime;
	uint64_t    earliestPresentTime;
	uint64_t    presentMargin;
} VkPastPresentationTimingGOOGLE;

typedef struct VkPresentTimeGOOGLE {
	uint32_t    presentID;
	uint64_t    desiredPresentTime;
} VkPresentTimeGOOGLE;

typedef struct VkPresentTimesInfoGOOGLE {
	VkStructureType               sType;
	const void*                   pNext;
	uint32_t                      swapchainCount;
	const VkPresentTimeGOOGLE*    pTimes;
} VkPresentTimesInfoGOOGLE;


typedef VkResult(VKAPI_PTR *PFN_vkGetRefreshCycleDurationGOOGLE)(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties);
typedef VkResult(VKAPI_PTR *PFN_vkGetPastPresentationTimingGOOGLE)(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetRefreshCycleDurationGOOGLE(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	VkRefreshCycleDurationGOOGLE*               pDisplayTimingProperties);

VKAPI_ATTR VkResult VKAPI_CALL vkGetPastPresentationTimingGOOGLE(
	VkDevice                                    device,
	VkSwapchainKHR                              swapchain,
	uint32_t*                                   pPresentationTimingCount,
	VkPastPresentationTimingGOOGLE*             pPresentationTimings);
#endif