#pragma once

struct VkFence_T : public vsrDeviceResource, public MemoryAlloc<VkFence_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkFence_T(const VkFenceCreateInfo* pCreateInfo);
	inline void Signal(bool bSignal)
	{
		_state = bSignal;
	}

	inline bool IsSignal() const
	{
		return _state;
	}

	std::atomic_bool _state;
};

struct VkSemaphore_T : public vsrDeviceResource, public MemoryAlloc<VkSemaphore_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkSemaphore_T(const VkSemaphoreCreateInfo* pCreateInfo);
	inline void Signal(bool bSignal)
	{
		_state = bSignal;
	}

	inline bool IsSignal() const
	{
		return _state;
	}
	
	std::atomic_bool _state;
};