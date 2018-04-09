#pragma once

enum vkCommandBufferState {
	CBS_Init = 0,
	CBS_Recording,
	CBS_Executable,
	CBS_Pending,
	CBS_Invalid,
};

struct VkCommandBuffer_T {
	vkCommandBufferState _state;
	VkCommandBufferLevel _level;
};

struct VkCommandPool_T {
	VkDevice_T *_device;
	VkCommandPoolCreateFlags _flag;
	uint32_t  _queueFamilyIndex;
	std::vector<VkCommandBuffer_T*> _commandBuffers;
	VkResult Allocate(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
};

