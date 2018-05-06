#include "vsr_common.h"
#include "vsr_framebuffer.h"

VkAllocationCallbacks *MemoryAlloc<VkFramebuffer_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkFramebuffer_T::VkFramebuffer_T(const VkFramebufferCreateInfo*   pCreateInfo)
	:_renderPass(pCreateInfo->renderPass),_width(pCreateInfo->width),_height(pCreateInfo->height),_layers(pCreateInfo->layers)
{
	for (uint32_t i = 0; i < pCreateInfo->attachmentCount; i++)
	{
		_vecAttachments.push_back(pCreateInfo->pAttachments[i]);
	}
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateFramebuffer(
	VkDevice                                    device,
	const VkFramebufferCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFramebuffer*                              pFramebuffer)
{
	try
	{
		*pFramebuffer = new(pAllocator) VkFramebuffer_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyFramebuffer(
	VkDevice                                    device,
	VkFramebuffer                               framebuffer,
	const VkAllocationCallbacks*                pAllocator)
{
	delete framebuffer;
}
