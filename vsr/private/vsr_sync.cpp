#include "vsr_common.h"
#include "vsr_sync.h"


VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(
	VkDevice                                    device,
	const VkFenceCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFence*                                    pFence)
{
	VkFence_T *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = (VkFence_T*)pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkFence_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
	}
	else
	{
		pMem = (VkFence_T*)std::malloc(sizeof(VkFence_T));
	}

	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	pMem->_state = false;
	pMem->_device = device;

	if (pCreateInfo->flags & VK_FENCE_CREATE_SIGNALED_BIT)
		pMem->_state = true;

	*pFence = pMem;
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(
	VkDevice                                    device,
	const VkSemaphoreCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSemaphore*                                pSemaphore)
{
	VkSemaphore_T *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = (VkSemaphore_T*)pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkSemaphore_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
	}
	else
	{
		pMem = (VkSemaphore_T*)std::malloc(sizeof(VkSemaphore_T));
	}

	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	pMem->_state = false;
	pMem->_device = device;

	*pSemaphore = pMem;
	return VK_SUCCESS;
}