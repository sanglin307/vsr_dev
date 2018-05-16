#include "vsr_common.h"
#include "vsr_memory.h"
#include "vsr_image.h"
#include "vsr_buffer.h"
#include "vsr_device.h"

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
	if (offset < 0 || size != VK_WHOLE_SIZE && offset + size >= _size)
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

	device->Registe(*pMemory);

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkFreeMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(memory);
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
	*ppData = memory->GetAddress(offset, size);
	if (*ppData == nullptr)
		return VK_ERROR_MEMORY_MAP_FAILED;

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(
	VkDevice                                    device,
	VkDeviceMemory                              memory)
{
	//do nothing.
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(
	VkDevice                                    device,
	VkBuffer                                    buffer,
	VkDeviceMemory                              memory,
	VkDeviceSize                                memoryOffset)
{
	void* pData = memory->GetAddress(memoryOffset, buffer->_size);
	if (pData == nullptr)
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	buffer->BindMemory(pData);
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(
	VkDevice                                    device,
	VkImage                                     image,
	VkDeviceMemory                              memory,
	VkDeviceSize                                memoryOffset)
{
	
	void* pData = memory->GetAddress(memoryOffset, image->_totalsize);
	if (pData == nullptr)
		return VK_ERROR_OUT_OF_DEVICE_MEMORY;

	image->BindMemory(pData);

	return VK_SUCCESS;
}