#pragma once

struct vQueueFamily {
	VkQueueFamilyProperties _property;
	VkBool32 _supportSurface;
};

struct VkQueue_T {
	uint32_t _queueFamilyIndex;
	float _priority;
};