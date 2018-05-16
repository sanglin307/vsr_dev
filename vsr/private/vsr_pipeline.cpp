#include "vsr_common.h"
#include "vsr_pipeline.h"
#include "vsr_device.h"
#include "vsr_shadermodule.h"

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

	device->Registe(*pPipelineCache);

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(
	VkDevice                                    device,
	VkPipelineCache                             pipelineCache,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(pipelineCache);
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
	_flags = pCreateInfos->flags;
	_layout = pCreateInfos->layout;
	_renderPass = pCreateInfos->renderPass;
	_subpass = pCreateInfos->subpass;

	assert(pCreateInfos->stageCount > 0);
	for (uint32_t i = 0; i < pCreateInfos->stageCount; i++)
	{
		vsrShaderStage ss;
		ss._stage = pCreateInfos->pStages[i].stage;
		ss._code = pCreateInfos->pStages[i].module->_vecCodes;
		assert(std::strlen(pCreateInfos->pStages[i].pName) < VK_ShaderStageNameLength);
		std::strncpy(ss._name, pCreateInfos->pStages[i].pName, VK_ShaderStageNameLength);
		for (uint32_t j = 0; j < pCreateInfos->pStages[i].pSpecializationInfo->mapEntryCount; j++)
		{
			ss._vecMapEntries.push_back(pCreateInfos->pStages[i].pSpecializationInfo->pMapEntries[j]);
		}
		ss._dataSize = pCreateInfos->pStages[i].pSpecializationInfo->dataSize;
		ss._pData = pCreateInfos->pStages[i].pSpecializationInfo->pData;

		_vecStages.push_back(ss);
	}

	assert(pCreateInfos->pVertexInputState->vertexBindingDescriptionCount > 0);
	assert(pCreateInfos->pVertexInputState->vertexAttributeDescriptionCount > 0);
	for (uint32_t i = 0; i < pCreateInfos->pVertexInputState->vertexBindingDescriptionCount; i++)
	{
		_vecVertexBindingDescriptions.push_back(pCreateInfos->pVertexInputState->pVertexBindingDescriptions[i]);
	}
	for (uint32_t i = 0; i < pCreateInfos->pVertexInputState->vertexAttributeDescriptionCount; i++)
	{
		_vecVertexAttributeDescriptions.push_back(pCreateInfos->pVertexInputState->pVertexAttributeDescriptions[i]);
	}
	_topology = pCreateInfos->pInputAssemblyState->topology;
	_primitiveRestartEnable = pCreateInfos->pInputAssemblyState->primitiveRestartEnable;

	if(pCreateInfos->pTessellationState != nullptr)
	   _patchControlPoints = pCreateInfos->pTessellationState->patchControlPoints;

	if (pCreateInfos->pViewportState != nullptr)
	{
		for (uint32_t i = 0; i < pCreateInfos->pViewportState->scissorCount; i++)
		{
			_vecScissors.push_back(pCreateInfos->pViewportState->pScissors[i]);
		}
		for (uint32_t i = 0; i < pCreateInfos->pViewportState->viewportCount; i++)
		{
			_vecViewports.push_back(pCreateInfos->pViewportState->pViewports[i]);
		}
	}

	assert(pCreateInfos->pRasterizationState != nullptr); 
	_depthClampEnable = pCreateInfos->pRasterizationState->depthClampEnable;
	_rasterizerDiscardEnable = pCreateInfos->pRasterizationState->rasterizerDiscardEnable;
	_polygonMode = pCreateInfos->pRasterizationState->polygonMode;
	_cullMode = pCreateInfos->pRasterizationState->cullMode;
	_frontFace = pCreateInfos->pRasterizationState->frontFace;
	_depthBiasEnable = pCreateInfos->pRasterizationState->depthBiasEnable;
	_depthBiasConstantFactor = pCreateInfos->pRasterizationState->depthBiasConstantFactor;
	_depthBiasClamp = pCreateInfos->pRasterizationState->depthBiasClamp;
	_depthBiasSlopeFactor = pCreateInfos->pRasterizationState->depthBiasSlopeFactor;
	_lineWidth = pCreateInfos->pRasterizationState->lineWidth;
	 
	if (pCreateInfos->pMultisampleState != nullptr)
	{
		_rasterizationSamples = pCreateInfos->pMultisampleState->rasterizationSamples;
		_sampleShadingEnable = pCreateInfos->pMultisampleState->sampleShadingEnable;
		_minSampleShading = pCreateInfos->pMultisampleState->minSampleShading;
		_alphaToCoverageEnable = pCreateInfos->pMultisampleState->alphaToCoverageEnable;
		_alphaToOneEnable = pCreateInfos->pMultisampleState->alphaToOneEnable;
	}
	else
	{
		_rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		_sampleShadingEnable = false;
		_minSampleShading = 0.f;
		_alphaToCoverageEnable = false;
		_alphaToOneEnable = false;
	}

	if (pCreateInfos->pDepthStencilState != nullptr)
	{
		_depthTestEnable = pCreateInfos->pDepthStencilState->depthTestEnable;
		_depthWriteEnable = pCreateInfos->pDepthStencilState->depthWriteEnable;
		_depthCompareOp = pCreateInfos->pDepthStencilState->depthCompareOp;
		_depthBoundsTestEnable = pCreateInfos->pDepthStencilState->depthBoundsTestEnable;
		_stencilTestEnable = pCreateInfos->pDepthStencilState->stencilTestEnable;
		_front = pCreateInfos->pDepthStencilState->front;
		_back = pCreateInfos->pDepthStencilState->back;
		_minDepthBounds = pCreateInfos->pDepthStencilState->minDepthBounds;
		_maxDepthBounds = pCreateInfos->pDepthStencilState->maxDepthBounds;
	}
	else
	{
		_depthTestEnable = false;
		_depthWriteEnable = false;
		_depthCompareOp = VK_COMPARE_OP_NEVER;
		_depthBoundsTestEnable = false;
		_stencilTestEnable = false;
		std::memset(&_front, 0, sizeof(_front));  
		std::memset(&_back, 0, sizeof(_back));
		_minDepthBounds = 0.f;
		_maxDepthBounds = 0.f;
	}

	if (pCreateInfos->pColorBlendState != nullptr)
	{
		_blendLogicOpEnable = pCreateInfos->pColorBlendState->logicOpEnable;
		_blendLogicOp = pCreateInfos->pColorBlendState->logicOp;
		for (uint32_t i = 0; i < pCreateInfos->pColorBlendState->attachmentCount; i++)
		{
			_vecBlendAttachments.push_back(pCreateInfos->pColorBlendState->pAttachments[i]);
		}
		std::memcpy(_blendConstants, pCreateInfos->pColorBlendState->blendConstants,sizeof(_blendConstants));
	}
	else
	{
		_blendLogicOpEnable = false;
		_blendLogicOp = VK_LOGIC_OP_CLEAR;
		std::memset(_blendConstants, 0, sizeof(_blendConstants));
	}

	if (pCreateInfos->pDynamicState != nullptr)
	{
		for (uint32_t i = 0; i < pCreateInfos->pDynamicState->dynamicStateCount; i++)
		{
			_vecDynamicStates.push_back(pCreateInfos->pDynamicState->pDynamicStates[i]);
		}
	}
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

	for (uint32_t i = 0; i < createInfoCount; i++)
	{
		device->Registe(pPipelines[i]);
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
	device->UnRegiste(pipeline);
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
	device->Registe(*pPipelineLayout);
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(
	VkDevice                                    device,
	VkPipelineLayout                            pipelineLayout,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(pipelineLayout);
	delete pipelineLayout;
}

