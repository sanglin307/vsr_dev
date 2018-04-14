#pragma once

struct vQueueFamily {
	VkQueueFamilyProperties _property;
	VkBool32 _supportSurface;
};

struct VkQueue_T : public MemoryAlloc<VkQueue_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	VkQueue_T(uint32_t familyIndex, float priority)
		:_queueFamilyIndex(familyIndex),_priority(priority)
	{
	}
	uint32_t _queueFamilyIndex;
	float _priority;
};