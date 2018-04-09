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