#pragma once

struct VkFence_T {
	VkDevice_T*  _device;
	std::atomic_bool _state;
};

struct VkSemaphore_T {
	VkDevice_T*  _device;
	std::atomic_bool _state;
};