#pragma once

struct VkFence_T : public MemoryAlloc<VkFence_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkFence_T(VkDevice device, const VkFenceCreateInfo* pCreateInfo);
	inline void Signal(bool bSignal)
	{
		_state = bSignal;
	}

	inline bool IsSignal() const
	{
		return _state;
	}

	VkDevice_T*  _device;
	std::atomic_bool _state;
};

struct VkSemaphore_T : public MemoryAlloc<VkSemaphore_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkSemaphore_T(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo);
	inline void Signal(bool bSignal)
	{
		_state = bSignal;
	}

	inline bool IsSignal() const
	{
		return _state;
	}
	VkDevice_T*  _device;
	std::atomic_bool _state;
};