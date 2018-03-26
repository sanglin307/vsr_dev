#pragma once

#include "vsr_define.h"
#include "vsr_renderpass.h"

VK_DEFINE_HANDLE(VkCommandBuffer)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCommandPool)

typedef enum VkCommandBufferLevel {
	VK_COMMAND_BUFFER_LEVEL_PRIMARY = 0,
	VK_COMMAND_BUFFER_LEVEL_SECONDARY = 1,
	VK_COMMAND_BUFFER_LEVEL_BEGIN_RANGE = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	VK_COMMAND_BUFFER_LEVEL_END_RANGE = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
	VK_COMMAND_BUFFER_LEVEL_RANGE_SIZE = (VK_COMMAND_BUFFER_LEVEL_SECONDARY - VK_COMMAND_BUFFER_LEVEL_PRIMARY + 1),
	VK_COMMAND_BUFFER_LEVEL_MAX_ENUM = 0x7FFFFFFF
} VkCommandBufferLevel;

typedef enum VkCommandBufferUsageFlagBits {
	VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT = 0x00000001,
	VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT = 0x00000002,
	VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT = 0x00000004,
	VK_COMMAND_BUFFER_USAGE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VkCommandBufferUsageFlagBits;
typedef VkFlags VkCommandBufferUsageFlags;

typedef enum VkCommandPoolCreateFlagBits {
	VK_COMMAND_POOL_CREATE_TRANSIENT_BIT = 0x00000001,
	VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT = 0x00000002,
	VK_COMMAND_POOL_CREATE_PROTECTED_BIT = 0x00000004,
	VK_COMMAND_POOL_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VkCommandPoolCreateFlagBits;

typedef enum VkCommandPoolResetFlagBits {
	VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT = 0x00000001,
	VK_COMMAND_POOL_RESET_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VkCommandPoolResetFlagBits;
typedef VkFlags VkCommandPoolResetFlags;

typedef struct VkCommandBufferAllocateInfo {
	VkStructureType         sType;
	const void*             pNext;
	VkCommandPool           commandPool;
	VkCommandBufferLevel    level;
	uint32_t                commandBufferCount;
} VkCommandBufferAllocateInfo;

typedef struct VkCommandBufferInheritanceInfo {
	VkStructureType                  sType;
	const void*                      pNext;
	VkRenderPass                     renderPass;
	uint32_t                         subpass;
	VkFramebuffer                    framebuffer;
	VkBool32                         occlusionQueryEnable;
	VkQueryControlFlags              queryFlags;
	VkQueryPipelineStatisticFlags    pipelineStatistics;

} VkCommandBufferInheritanceInfo;
typedef struct VkCommandBufferBeginInfo {
	VkStructureType                          sType;
	const void*                              pNext;
	VkCommandBufferUsageFlags                flags;
	const VkCommandBufferInheritanceInfo*    pInheritanceInfo;
} VkCommandBufferBeginInfo;


typedef VkFlags VkCommandPoolCreateFlags;
typedef struct VkCommandPoolCreateInfo {
	VkStructureType             sType;
	const void*                 pNext;
	VkCommandPoolCreateFlags    flags;
	uint32_t                    queueFamilyIndex;
} VkCommandPoolCreateInfo;
 
VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(
	VkDevice                                    device,
	const VkCommandPoolCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkCommandPool*                              pCommandPool);

VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	const VkAllocationCallbacks*                pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	VkCommandPoolResetFlags                     flags);

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateCommandBuffers(
	VkDevice                                    device,
	const VkCommandBufferAllocateInfo*          pAllocateInfo,
	VkCommandBuffer*                            pCommandBuffers);

VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	uint32_t                                    commandBufferCount,
	const VkCommandBuffer*                      pCommandBuffers);

VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(
	VkCommandBuffer                             commandBuffer,
	const VkCommandBufferBeginInfo*             pBeginInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkEndCommandBuffer(
	VkCommandBuffer                             commandBuffer);

VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandBuffer(
	VkCommandBuffer                             commandBuffer,
	VkCommandBufferResetFlags                   flags);
