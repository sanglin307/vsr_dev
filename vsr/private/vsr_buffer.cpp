#include "vsr_common.h"

VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	VkMemoryRequirements*                       pMemoryRequirements)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateBuffer(
	VkDevice                                    device,
	const VkBufferCreateInfo*                   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkBuffer*                                   pBuffer)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	const VkAllocationCallbacks*                pAllocator)
{

}