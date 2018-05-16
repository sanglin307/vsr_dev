#pragma once

struct VkDeviceMemory_T : public vsrDeviceResource,public MemoryAlloc<VkDeviceMemory_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkDeviceMemory_T(VkDeviceSize size, uint32_t typeIndex);
	~VkDeviceMemory_T();

	void* GetAddress(VkDeviceSize offset, VkDeviceSize size);

	VkDeviceSize       _size;
	uint32_t           _typeIndex;
	void               *_pData;
};