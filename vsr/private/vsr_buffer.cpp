#include "vsr_common.h"
#include "vsr_device.h"
#include "vsr_physicaldevice.h"
#include "vsr_buffer.h"

VkAllocationCallbacks *MemoryAlloc<VkBuffer_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkBuffer_T::VkBuffer_T(const VkBufferCreateInfo* pCreateInfo)
	:_size(pCreateInfo->size),_usage(pCreateInfo->usage),_sharingMode(pCreateInfo->sharingMode),_pData(nullptr)
{
	if (_sharingMode == VK_SHARING_MODE_CONCURRENT)
	{
		for (size_t i = 0; i < pCreateInfo->queueFamilyIndexCount; i++)
		{
			_vecQueueFamilyIndex.push_back(pCreateInfo->pQueueFamilyIndices[i]);
		}
	}
}

void VkBuffer_T::GetBufferMemoryRequirements(VkDevice device, VkMemoryRequirements* pMemoryRequirements)
{
	pMemoryRequirements->alignment = Vk_Allocation_Alignment;
	pMemoryRequirements->size = _size;
	VkPhysicalDeviceMemoryProperties prop;
	device->_physicalDevice->GetPhysicalDeviceMemoryProperties(&prop);
	for (uint32_t i = 0; i < prop.memoryTypeCount; i++)
		pMemoryRequirements->memoryTypeBits |= 1 << i;			 
}


VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	VkMemoryRequirements*                       pMemoryRequirements)
{
	buffer->GetBufferMemoryRequirements(device, pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateBuffer(
	VkDevice                                    device,
	const VkBufferCreateInfo*                   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkBuffer*                                   pBuffer)
{
	try
	{
		*pBuffer = new(pAllocator) VkBuffer_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	const VkAllocationCallbacks*                pAllocator)
{
	delete buffer;
}