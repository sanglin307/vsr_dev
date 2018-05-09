#include "vsr_common.h"
#include "vsr_queue.h"
#include "vsr_command.h"

VkAllocationCallbacks *MemoryAlloc<VkQueue_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(
	VkQueue                                     queue,
	uint32_t                                    submitCount,
	const VkSubmitInfo*                         pSubmits,
	VkFence                                     fence)
{
	for (uint32_t i = 0; i < submitCount; i++)
	{
		vsrQueueSubmit *pS = new vsrQueueSubmit;
		for (uint32_t j = 0; j < pSubmits[i].waitSemaphoreCount; j++)
		{
			pS->_vecWaitSemaphores.push_back(pSubmits[i].pWaitSemaphores[j]);
			pS->_vecWaitDstStageMask.push_back(pSubmits[i].pWaitDstStageMask[j]);
		}

		for (uint32_t j = 0; j < pSubmits[i].commandBufferCount; j++)
			pS->_vecCommandBuffers.push_back(pSubmits[i].pCommandBuffers[j]);

		for (uint32_t j = 0; j < pSubmits[i].signalSemaphoreCount; j++)
			pS->_vecSignalSemaphores.push_back(pSubmits[i].pSignalSemaphores[j]);
		
		if (i == submitCount - 1)
			pS->_fence = fence;
		else
			pS->_fence = nullptr;
		
		queue->_listSubmit.push_back(pS);
	}

	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueueWaitIdle(
	VkQueue                                     queue)
{
	return VK_SUCCESS;
}