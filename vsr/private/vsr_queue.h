#pragma once

struct vsrQueueFamily {
	VkQueueFamilyProperties  _property;
	VkBool32                 _supportSurface;
};

struct vsrQueueSubmit {
	std::vector<VkSemaphore>             _vecWaitSemaphores;
	std::vector<VkPipelineStageFlags>    _vecWaitDstStageMask;
	std::vector<VkCommandBuffer>         _vecCommandBuffers;
	std::vector<VkSemaphore>             _vecSignalSemaphores;
	VkFence                              _fence;
};


struct VkQueue_T : public MemoryAlloc<VkQueue_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkQueue_T(uint32_t familyIndex, float priority)
		:_queueFamilyIndex(familyIndex),_priority(priority)
	{
	}
	uint32_t _queueFamilyIndex;
	float    _priority;
	std::list<vsrQueueSubmit*>  _listSubmit;
};