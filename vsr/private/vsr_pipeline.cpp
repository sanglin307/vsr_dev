#include "vsr_common.h"

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(
	VkDevice                                    device,
	const VkPipelineCacheCreateInfo*            pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkPipelineCache*                            pPipelineCache)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	const VkAllocationCallbacks*                pAllocator)
{}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineCacheData(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	size_t*                                     pDataSize,
	void*                                       pData)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkMergePipelineCaches(
	VkDevice                                    device,
	VkPipelineCache                             dstCache,
	uint32_t                                    srcCacheCount,
	const VkPipelineCache*                      pSrcCaches)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateGraphicsPipelines(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	uint32_t                                    createInfoCount,
	const VkGraphicsPipelineCreateInfo*         pCreateInfos,
	const VkAllocationCallbacks*                pAllocator,
	VkPipeline*                                 pPipelines)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateComputePipelines(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	uint32_t                                    createInfoCount,
	const VkComputePipelineCreateInfo*          pCreateInfos,
	const VkAllocationCallbacks*                pAllocator,
	VkPipeline*                                 pPipelines)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(
	VkDevice                                    device,
	VkPipeline                                  pipeline,
	const VkAllocationCallbacks*                pAllocator)
{}

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(
	VkDevice                                    device,
	const VkPipelineLayoutCreateInfo*           pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkPipelineLayout*                           pPipelineLayout)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(
	VkDevice                                    device,
	VkPipelineLayout                            pipelineLayout,
	const VkAllocationCallbacks*                pAllocator)
{}

