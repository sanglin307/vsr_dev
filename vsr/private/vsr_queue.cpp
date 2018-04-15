#include "vsr_common.h"
#include "vsr_queue.h"

VkAllocationCallbacks *MemoryAlloc<VkQueue_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(
	VkQueue                                     queue,
	uint32_t                                    submitCount,
	const VkSubmitInfo*                         pSubmits,
	VkFence                                     fence)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkQueueWaitIdle(
	VkQueue                                     queue)
{
	return VK_SUCCESS;
}