#include "vsr_common.h"
#include "vsr_queue.h"
#include "vsr_command.h"

void VkQueue_T::Push(vsrQueueJob* job)
{
	std::lock_guard<std::mutex> lock(_listMutex);
	_listJob.push_back(job);
}

bool VkQueue_T::Empty()
{
	std::lock_guard<std::mutex> lock(_listMutex);
	return _listJob.empty();
}

VkQueue_T::~VkQueue_T()
{
	std::lock_guard<std::mutex> lock(_listMutex);
	for (auto v : _listJob)
	{
		delete v;
	}
}

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
		
		queue->Push(pS);
	}

	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(
	VkQueue                                     queue,
	const VkPresentInfoKHR*                     pPresentInfo)
{
	vsrQueuePresent *pJob = new vsrQueuePresent;
	for (uint32_t i = 0; i < pPresentInfo->waitSemaphoreCount; i++)
	{
		pJob->_vecWaitSemaphores.push_back(pPresentInfo->pWaitSemaphores[i]);
	}
	for (uint32_t i = 0; i < pPresentInfo->swapchainCount; i++)
	{
		vsrQueuePresentSwapchain sc = {
			pPresentInfo->pSwapchains[i],
			pPresentInfo->pImageIndices[i]
		};
		pJob->_vecSwapchains.push_back(sc);
		if (pPresentInfo->pResults != nullptr)
			pPresentInfo->pResults[i] = VK_SUCCESS;
	}

	queue->Push(pJob);

	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueueWaitIdle(
	VkQueue                                     queue)
{
	while (!queue->Empty())
		std::this_thread::yield();

	return VK_SUCCESS;
}