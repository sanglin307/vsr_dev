#include "vsr_common.h"
#include "vsr_command.h"



VKAPI_ATTR VkResult VKAPI_CALL vkAllocateCommandBuffers(
	VkDevice                                    device,
	const VkCommandBufferAllocateInfo*          pAllocateInfo,
	VkCommandBuffer*                            pCommandBuffers)
{
	return pAllocateInfo->commandPool->Allocate(pAllocateInfo, pCommandBuffers);
}

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


VkResult VkCommandPool_T::Allocate(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
	assert(pAllocateInfo->commandBufferCount > 0);
	for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++)
	{
		VkCommandBuffer_T *pBuffer = new VkCommandBuffer_T;
		pBuffer->_level = pAllocateInfo->level;
		pBuffer->_state = CBS_Init;
		_commandBuffers.push_back(pBuffer);
	}

	*pCommandBuffers = _commandBuffers[_commandBuffers.size() - pAllocateInfo->commandBufferCount];
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(
	VkDevice                                    device,
	const VkCommandPoolCreateInfo*              pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkCommandPool*                              pCommandPool)
{
	VkCommandPool_T *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = (VkCommandPool_T*)pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkCommandPool_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
	}
	else
	{
		pMem = (VkCommandPool_T*)std::malloc(sizeof(VkCommandPool_T));
	}

	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	pMem->_device = device;
	pMem->_flag = pCreateInfo->flags;
	pMem->_queueFamilyIndex = pCreateInfo->queueFamilyIndex;

	*pCommandPool = pMem;

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	const VkAllocationCallbacks*                pAllocator)
{
	if (pAllocator != nullptr)
	{
		pAllocator->pfnFree(pAllocator->pUserData, commandPool);
	}
	else
	{
		std::free(commandPool);
	}
}


VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	VkCommandPoolResetFlags                     flags)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(
	VkDevice                                    device,
	VkCommandPool                               commandPool,
	uint32_t                                    commandBufferCount,
	const VkCommandBuffer*                      pCommandBuffers)
{}


VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(
	VkCommandBuffer                             commandBuffer,
	VkImage                                     srcImage,
	VkImageLayout                               srcImageLayout,
	VkImage                                     dstImage,
	VkImageLayout                               dstImageLayout,
	uint32_t                                    regionCount,
	const VkImageCopy*                          pRegions)
{

}

VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipeline                                  pipeline)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdSetViewport(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstViewport,
	uint32_t                                    viewportCount,
	const VkViewport*                           pViewports)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdSetScissor(
	VkCommandBuffer                             commandBuffer,
	uint32_t                                    firstScissor,
	uint32_t                                    scissorCount,
	const VkRect2D*                             pScissors)
{}

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
{}

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
{}

VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass(
	VkCommandBuffer                             commandBuffer,
	VkSubpassContents                           contents)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass(
	VkCommandBuffer                             commandBuffer)
{}