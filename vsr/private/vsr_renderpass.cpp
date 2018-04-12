#include "vsr_common.h"


VKAPI_ATTR VkResult VKAPI_CALL vkCreateFramebuffer(
	VkDevice                                    device,
	const VkFramebufferCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFramebuffer*                              pFramebuffer)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyFramebuffer(
	VkDevice                                    device,
	VkFramebuffer                               framebuffer,
	const VkAllocationCallbacks*                pAllocator)
{}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass(
	VkDevice                                    device,
	const VkRenderPassCreateInfo*               pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkRenderPass*                               pRenderPass)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyRenderPass(
	VkDevice                                    device,
	VkRenderPass                                renderPass,
	const VkAllocationCallbacks*                pAllocator)
{}