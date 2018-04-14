#pragma once

struct vQueueFamily {
	VkQueueFamilyProperties _property;
	VkBool32 _supportSurface;
};

struct VkQueue_T : public MemoryAlloc<VkQueue_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	uint32_t _queueFamilyIndex;
	float _priority;
};