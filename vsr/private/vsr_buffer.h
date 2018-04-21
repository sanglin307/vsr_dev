#pragma once

struct VkBuffer_T : public MemoryAlloc<VkBuffer_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkBuffer_T(const VkBufferCreateInfo* pCreateInfo);
	void GetBufferMemoryRequirements(VkDevice device, VkMemoryRequirements* pMemoryRequirements);
	inline void BindMemory(void* pData)
	{
		_pData = pData;
	}

	VkDeviceSize           _size;
	VkBufferUsageFlags     _usage;
	VkSharingMode          _sharingMode;
	std::vector<uint32_t>  _vecQueueFamilyIndex;
	void*                            _pData;
};