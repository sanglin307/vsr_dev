#include "vsr_common.h"
#include "vsr_memory.h"
#include "vsr_image.h"

VkAllocationCallbacks *MemoryAlloc<VkDeviceMemory_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;

VkDeviceMemory_T::VkDeviceMemory_T(VkDeviceSize size, uint32_t typeIndex)
	:_size(size),_typeIndex(typeIndex),_pData(nullptr)
{
	_pData = std::malloc(size);
	if (_pData == nullptr)
		throw std::bad_alloc();
}

VkDeviceMemory_T::~VkDeviceMemory_T()
{
	if (_pData != nullptr)
	{
		std::free(_pData);
		_pData = nullptr;
	}
}

void* VkDeviceMemory_T::GetAddress(VkDeviceSize offset,VkDeviceSize size)
{
	assert(_pData != nullptr);
	if (offset < 0 || size <= 0 || offset + size >= _size)
		return nullptr;

	return (void*)((uint8_t*)_pData + offset);
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateMemory(
	VkDevice                                    device,
	const VkMemoryAllocateInfo*                 pAllocateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDeviceMemory*                             pMemory)
{
	try
	{
		*pMemory = new(pAllocator) VkDeviceMemory_T(pAllocateInfo->allocationSize,pAllocateInfo->memoryTypeIndex);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkFreeMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory,
	const VkAllocationCallbacks*                pAllocator)
{
	delete memory;
}

VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory,
	VkDeviceSize                                offset,
	VkDeviceSize                                size,
	VkMemoryMapFlags                            flags,
	void**                                      ppData)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	VkDeviceMemory                              memory,
	VkDeviceSize                                memoryOffset)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(
	VkDevice                                    device,
	VkImage                                     image,
	VkDeviceMemory                              memory,
	VkDeviceSize                                memoryOffset)
{
	
	void* pData = memory->GetAddress(memoryOffset, image->_size);
	if (pData == nullptr)
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	image->BindMemory(pData);

	return VK_SUCCESS;
}