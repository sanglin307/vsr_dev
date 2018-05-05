#include "vsr_common.h"
#include "vsr_renderpass.h"

VkAllocationCallbacks *MemoryAlloc<VkRenderPass_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkRenderPass_T::VkRenderPass_T(const VkRenderPassCreateInfo* pCreateInfo)
{
	for (uint32_t i = 0; i < pCreateInfo->attachmentCount; i++)
	{
		_vecAttachment.push_back(pCreateInfo->pAttachments[i]);
	}

	for (uint32_t i = 0; i < pCreateInfo->subpassCount; i++)
	{
		_vecSubpasses.push_back(pCreateInfo->pSubpasses[i]);
	}

	for (uint32_t i = 0; i < pCreateInfo->dependencyCount; i++)
	{
		_vecDependencies.push_back(pCreateInfo->pDependencies[i]);
	}
}



VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass(
	VkDevice                                    device,
	const VkRenderPassCreateInfo*               pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkRenderPass*                               pRenderPass)
{
	try
	{
		*pRenderPass = new(pAllocator) VkRenderPass_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyRenderPass(
	VkDevice                                    device,
	VkRenderPass                                renderPass,
	const VkAllocationCallbacks*                pAllocator)
{
	delete renderPass;
}