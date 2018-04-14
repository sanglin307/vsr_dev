#pragma once

struct VkFence_T : public MemoryAlloc<VkFence_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	VkFence_T(VkDevice device, const VkFenceCreateInfo* pCreateInfo);
	VkDevice_T*  _device;
	std::atomic_bool _state;
};

struct VkSemaphore_T : public MemoryAlloc<VkSemaphore_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	VkSemaphore_T(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo);
	VkDevice_T*  _device;
	std::atomic_bool _state;
};