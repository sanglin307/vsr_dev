#include "vsr_common.h"
#include "vsr_sync.h"


VkAllocationCallbacks *MemoryAlloc<VkFence_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkFence_T::VkFence_T(VkDevice device, const VkFenceCreateInfo* pCreateInfo)
{
	_state = false;
	_device = device;

	if (pCreateInfo->flags & VK_FENCE_CREATE_SIGNALED_BIT)
		_state = true;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(
	VkDevice                                    device,
	const VkFenceCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkFence*                                    pFence)
{
	try
	{
		*pFence = new(pAllocator) VkFence_T(device,pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}
 
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyFence(
	VkDevice                                    device,
	VkFence                                     fence,
	const VkAllocationCallbacks*                pAllocator)
{
	delete fence;
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceStatus(
	VkDevice                                    device,
	VkFence                                     fence)
{
	if (fence->IsSignal())
		return VK_SUCCESS;
	else
		return VK_NOT_READY;
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(
	VkDevice                                    device,
	uint32_t                                    fenceCount,
	const VkFence*                              pFences)
{
	for (uint32_t i = 0; i < fenceCount; i++)
	{
		pFences[i]->Signal(false);
	}
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(
	VkDevice                                    device,
	uint32_t                                    fenceCount,
	const VkFence*                              pFences,
	VkBool32                                    waitAll,
	uint64_t                                    timeout)
{
	auto begin = std::chrono::high_resolution_clock::now();
	while (true)
	{
		bool bAll = true;
		for (uint32_t i = 0; i < fenceCount; i++)
		{
			if (!pFences[i]->IsSignal())
				bAll = false;
			else
			{
				if (!waitAll)
					return VK_SUCCESS;
			}
		}

		if (waitAll && bAll)
			return VK_SUCCESS;
		else
		{
			auto now = std::chrono::high_resolution_clock::now();
			if (uint64_t((now - begin).count()) > timeout)
				return VK_TIMEOUT;
		}
		std::this_thread::yield();
		
	}
	
	return VK_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

VkAllocationCallbacks *MemoryAlloc<VkSemaphore_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkSemaphore_T::VkSemaphore_T(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo)
	:_device(device),_state(false)
{
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(
	VkDevice                                    device,
	const VkSemaphoreCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSemaphore*                                pSemaphore)
{
	try
	{
		*pSemaphore = new(pAllocator) VkSemaphore_T(device, pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(
	VkDevice                                    device,
	VkSemaphore                                 semaphore,
	const VkAllocationCallbacks*                pAllocator)
{
	delete semaphore;
}



