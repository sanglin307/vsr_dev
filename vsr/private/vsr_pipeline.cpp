#include "vsr_common.h"
#include "vsr_pipeline.h"
#include "vsr_device.h"

VkAllocationCallbacks *MemoryAlloc<VkPipelineLayout_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkPipelineLayout_T::VkPipelineLayout_T(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo)
{
	for (uint32_t i = 0; i < pCreateInfo->setLayoutCount; i++)
	{
		_vecSetLayouts.push_back(pCreateInfo->pSetLayouts[i]);
	}

	for (uint32_t i = 0; i < pCreateInfo->pushConstantRangeCount; i++)
	{
		_vecPushConstantRanges.push_back(pCreateInfo->pPushConstantRanges[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VkAllocationCallbacks *MemoryAlloc<VkPipelineCache_T, VK_SYSTEM_ALLOCATION_SCOPE_CACHE>::_pAllocator = nullptr;
VkPipelineCache_T::VkPipelineCache_T(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo)
{
	if (pCreateInfo->initialDataSize > 0)
	{
		uint8_t *pbegin = nullptr; 
		if (_vecData.size() > 0)
		{
			pbegin = &(_vecData[_vecData.size()-1]);
			_vecData.resize(_vecData.size() + pCreateInfo->initialDataSize);
			std::memcpy(pbegin, pCreateInfo->pInitialData, pCreateInfo->initialDataSize);
		}
		else
		{
			_vecData.resize(pCreateInfo->initialDataSize);
			std::memcpy(_vecData.data(), pCreateInfo->pInitialData, pCreateInfo->initialDataSize);
		}
	}
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(
	VkDevice                                    device,
	const VkPipelineCacheCreateInfo*            pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkPipelineCache*                            pPipelineCache)
{
	try
	{
		*pPipelineCache = new(pAllocator) VkPipelineCache_T(device, pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	const VkAllocationCallbacks*                pAllocator)
{
	delete pipelineCache;
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineCacheData(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	size_t*                                     pDataSize,
	void*                                       pData)
{
	*pDataSize = pipelineCache->_vecData.size();
	if (pData != nullptr)
		std::memcpy(pData, pipelineCache->_vecData.data(), pipelineCache->_vecData.size());

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VkAllocationCallbacks *MemoryAlloc<VkPipeline_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkPipeline_T::VkPipeline_T(VkDevice device,const VkGraphicsPipelineCreateInfo* pCreateInfos)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateGraphicsPipelines(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	uint32_t                                    createInfoCount,
	const VkGraphicsPipelineCreateInfo*         pCreateInfos,
	const VkAllocationCallbacks*                pAllocator,
	VkPipeline*                                 pPipelines)
{
	try
	{
		for (uint32_t i = 0; i < createInfoCount; i++)
		{
			pPipelines[i] = new(pAllocator) VkPipeline_T(device,&(pCreateInfos[i]));
		}
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

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
{
	delete pipeline;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(
	VkDevice                                    device,
	const VkPipelineLayoutCreateInfo*           pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkPipelineLayout*                           pPipelineLayout)
{
	try
	{
		*pPipelineLayout = new(pAllocator) VkPipelineLayout_T(device,pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(
	VkDevice                                    device,
	VkPipelineLayout                            pipelineLayout,
	const VkAllocationCallbacks*                pAllocator)
{
	delete pipelineLayout;
}

