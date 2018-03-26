#pragma once

#include "vsr_define.h"

typedef enum VkFenceCreateFlagBits {
	VK_FENCE_CREATE_SIGNALED_BIT = 0x00000001,
	VK_FENCE_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VkFenceCreateFlagBits;
typedef VkFlags VkFenceCreateFlags;
typedef VkFlags VkSemaphoreCreateFlags;
typedef VkFlags VkEventCreateFlags;
typedef VkFlags VkQueryPoolCreateFlags;

typedef struct VkFenceCreateInfo {
	VkStructureType       sType;
	const void*           pNext;
	VkFenceCreateFlags    flags;
} VkFenceCreateInfo;

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFence)

VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(
	VkDevice                                    device,
	const VkFenceCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFence*                                    pFence);

VKAPI_ATTR void VKAPI_CALL vkDestroyFence(
	VkDevice                                    device,
	VkFence                                     fence,
	const VkAllocationCallbacks*                pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(
	VkDevice                                    device,
	uint32_t                                    fenceCount,
	const VkFence*                              pFences);

VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceStatus(
	VkDevice                                    device,
	VkFence                                     fence);

VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(
	VkDevice                                    device,
	uint32_t                                    fenceCount,
	const VkFence*                              pFences,
	VkBool32                                    waitAll,
	uint64_t                                    timeout);