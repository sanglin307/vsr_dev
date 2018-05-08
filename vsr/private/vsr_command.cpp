#include "vsr_common.h"
#include "vsr_command.h"
#include "vsr_image.h"
 
void vsrCmd_CopyImage::Excute()
{
	for (size_t i = 0; i < _vecRegions.size(); i++)
	{
		uint32_t layers = _vecRegions[i].srcSubresource.layerCount;
		if(_srcImage->_type == VK_IMAGE_TYPE_3D && _dstImage->_type != VK_IMAGE_TYPE_3D)
			layers = _vecRegions[i].dstSubresource.layerCount;

		for (uint32_t i = 0; i < layers; i++)
		{
			void *pSrcData = _srcImage->GetMemory(_vecRegions[i].srcSubresource.baseArrayLayer + i, _vecRegions[i].srcSubresource.mipLevel, _vecRegions[i].srcOffset);
			void *pDstData = _dstImage->GetMemory(_vecRegions[i].dstSubresource.baseArrayLayer + i, _vecRegions[i].dstSubresource.mipLevel, _vecRegions[i].dstOffset);
			uint32_t size = _vecRegions[i].extent.width * _vecRegions[i].extent.height * _vecRegions[i].extent.depth * _srcImage->_elementsize;
			std::memcpy(pDstData, pSrcData, size);
		}
		

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VkAllocationCallbacks *MemoryAlloc<VkCommandPool_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;

VkResult VkCommandPool_T::Allocate(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
	assert(pAllocateInfo->commandBufferCount > 0);
	for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++)
	{
		VkCommandBuffer_T *pBuffer = new VkCommandBuffer_T(pAllocateInfo->level);
		_commandBuffers.push_back(pBuffer);
	}

	*pCommandBuffers = _commandBuffers[_commandBuffers.size() - pAllocateInfo->commandBufferCount];
	return VK_SUCCESS;
}

void VkCommandPool_T::Free(uint32_t commandBufferCount, const VkCommandBuffer*  pCommandBuffers)
{
	for (uint32_t i = 0; i < commandBufferCount; i++)
	{
		_commandBuffers.erase(std::find(_commandBuffers.begin(), _commandBuffers.end(), pCommandBuffers[i]));
		delete pCommandBuffers[i];
	}
}

VkCommandPool_T::VkCommandPool_T(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo)
{
	_device = device;
	_flag = pCreateInfo->flags;
	_queueFamilyIndex = pCreateInfo->queueFamilyIndex;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(
	VkDevice                                    device,
	const VkCommandPoolCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkCommandPool*                              pCommandPool)
{
	try
	{
		*pCommandPool = new(pAllocator) VkCommandPool_T(device, pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}
 
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	const VkAllocationCallbacks*                pAllocator)
{
	delete commandPool;
}


VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	VkCommandPoolResetFlags                     flags)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateCommandBuffers(
	VkDevice                                    device,
	const VkCommandBufferAllocateInfo*          pAllocateInfo,
	VkCommandBuffer*                            pCommandBuffers)
{
	return pAllocateInfo->commandPool->Allocate(pAllocateInfo, pCommandBuffers);
}

VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	uint32_t                                    commandBufferCount,
	const VkCommandBuffer*                      pCommandBuffers)
{
	commandPool->Free(commandBufferCount, pCommandBuffers);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(
	VkCommandBuffer                             commandBuffer,
	const VkCommandBufferBeginInfo*             pBeginInfo)
{
	assert(commandBuffer->_state == CBS_Init);
	commandBuffer->_state = CBS_Recording;
	//todo for secondary commandbuffer to process pInheritanceInfo.


	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkEndCommandBuffer(
	VkCommandBuffer                             commandBuffer)
{
	assert(commandBuffer->_state == CBS_Recording);
	commandBuffer->_state = CBS_Executable;

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     srcImage,
	VkImageLayout                               srcImageLayout,
	VkImage                                     dstImage,
	VkImageLayout                               dstImageLayout,
	uint32_t                                    regionCount,
	const VkImageCopy*                          pRegions)
{
	vsrCmd_CopyImage *pCmd = new vsrCmd_CopyImage;
	pCmd->_srcImage = srcImage;
	pCmd->_srcImageLayout = srcImageLayout;
	pCmd->_dstImage = dstImage;
	pCmd->_dstImageLayout = dstImageLayout;
	for (size_t i = 0; i < regionCount; i++)
	{
		VkImageCopy c = { pRegions[i].srcSubresource,pRegions[i].srcOffset,pRegions[i].dstSubresource,pRegions[i].dstOffset, pRegions[i].extent };
		pCmd->_vecRegions.push_back(c);
	}
	commandBuffer->_listCommands.push_back(pCmd);
}

VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipeline                                  pipeline)
{
	vsrCmd_BindPipeline *pCmd = new vsrCmd_BindPipeline;
	pCmd->_pipelineBindPoint = pipelineBindPoint;
	pCmd->_pipeline = pipeline;
	commandBuffer->_listCommands.push_back(pCmd);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewport(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstViewport,
	uint32_t                                    viewportCount,
	const VkViewport*                           pViewports)
{
	vsrCmd_SetViewport *pCmd = new vsrCmd_SetViewport;
	pCmd->_firstViewport = firstViewport;
	for (uint32_t i = 0; i < viewportCount; i++)
	{
		pCmd->_vecViewports.push_back(pViewports[i]);
	}
	commandBuffer->_listCommands.push_back(pCmd);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetScissor(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstScissor,
	uint32_t                                    scissorCount,
	const VkRect2D*                             pScissors)
{
	vsrCmd_SetScissor *pCmd = new vsrCmd_SetScissor;
	pCmd->_firstScissor = firstScissor;
	for (uint32_t i = 0; i < scissorCount; i++)
	{
		pCmd->_vecScissors.push_back(pScissors[i]);
	}
	commandBuffer->_listCommands.push_back(pCmd);
}

VKAPI_ATTR void VKAPI_CALL vkCmdSetLineWidth(
	VkCommandBuffer                             commandBuffer,
	float                                       lineWidth)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBias(
	VkCommandBuffer                             commandBuffer,
	float                                       depthBiasConstantFactor,
	float                                       depthBiasClamp,
	float                                       depthBiasSlopeFactor)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipelineLayout                            layout,
	uint32_t                                    firstSet,
	uint32_t                                    descriptorSetCount,
	const VkDescriptorSet*                      pDescriptorSets,
	uint32_t                                    dynamicOffsetCount,
	const uint32_t*                             pDynamicOffsets)
{
	vsrCmd_BindDescriptorSets *pCmd = new vsrCmd_BindDescriptorSets;
	pCmd->_pipelineBindPoint = pipelineBindPoint;
	pCmd->_layout = layout;
	pCmd->_firstSet = firstSet;

	for (uint32_t i = 0; i < descriptorSetCount; i++)
	{
		pCmd->_vecDescriptorSets.push_back(pDescriptorSets[i]);
	}

	for (uint32_t i = 0; i < dynamicOffsetCount; i++)
	{
		pCmd->_vecDynamicOffsets.push_back(pDynamicOffsets[i]);
	}
	commandBuffer->_listCommands.push_back(pCmd);
 }

VKAPI_ATTR void VKAPI_CALL vkCmdSetBlendConstants(
	VkCommandBuffer                             commandBuffer,
	const float                                 blendConstants[4])
{}

VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBounds(
	VkCommandBuffer                             commandBuffer,
	float                                       minDepthBounds,
	float                                       maxDepthBounds)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdDraw(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    vertexCount,
	uint32_t                                    instanceCount,
	uint32_t                                    firstVertex,
	uint32_t                                    firstInstance)
{
	vsrCmd_Draw *pCmd = new vsrCmd_Draw;
	pCmd->_vertexCount = vertexCount;
	pCmd->_instanceCount = instanceCount;
	pCmd->_firstVertex = firstVertex;
	pCmd->_firstInstance = firstInstance;
	commandBuffer->_listCommands.push_back(pCmd);
}

VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier(
	VkCommandBuffer                             commandBuffer,
	VkPipelineStageFlags                        srcStageMask,
	VkPipelineStageFlags                        dstStageMask,
	VkDependencyFlags                           dependencyFlags,
	uint32_t                                    memoryBarrierCount,
	const VkMemoryBarrier*                      pMemoryBarriers,
	uint32_t                                    bufferMemoryBarrierCount,
	const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
	uint32_t                                    imageMemoryBarrierCount,
	const VkImageMemoryBarrier*                 pImageMemoryBarriers)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass(
	VkCommandBuffer                             commandBuffer,
	const VkRenderPassBeginInfo*                pRenderPassBegin,
	VkSubpassContents                           contents)
{
	vsrCmd_BeginRenderPass *pCmd = new vsrCmd_BeginRenderPass;
	pCmd->_contents = contents;
	pCmd->_framebuffer = pRenderPassBegin->framebuffer;
	pCmd->_renderArea = pRenderPassBegin->renderArea;
	pCmd->_renderPass = pRenderPassBegin->renderPass;
	for (uint32_t i = 0; i < pRenderPassBegin->clearValueCount; i++)
	{
		pCmd->_vecClearValues.push_back(pRenderPassBegin->pClearValues[i]);
	}
	commandBuffer->_listCommands.push_back(pCmd);
}

VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass(
	VkCommandBuffer                             commandBuffer,
	VkSubpassContents                           contents)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass(
	VkCommandBuffer                             commandBuffer)
{
	vsrCmd_EndRenderPass *pCmd = new vsrCmd_EndRenderPass;
	commandBuffer->_listCommands.push_back(pCmd);
}