#pragma once

struct vsrQueueFamily {
	VkQueueFamilyProperties  _property;
	VkBool32                 _supportSurface;
};

struct vsrQueueJob {
	virtual void Run() = 0;
};

struct vsrQueueSubmit : public vsrQueueJob {
	virtual void Run();
	std::vector<VkSemaphore>             _vecWaitSemaphores;
	std::vector<VkPipelineStageFlags>    _vecWaitDstStageMask;
	std::vector<VkCommandBuffer>         _vecCommandBuffers;
	std::vector<VkSemaphore>             _vecSignalSemaphores;
	VkFence                              _fence;
};

struct vsrQueuePresentSwapchain {
	VkSwapchainKHR   _swapChain;
	uint32_t         _imageIndex;
};

struct vsrQueuePresent : public vsrQueueJob {
	virtual void Run();
	std::vector<VkSemaphore>                 _vecWaitSemaphores;
	std::vector<vsrQueuePresentSwapchain>    _vecSwapchains;
};


struct VkQueue_T : public MemoryAlloc<VkQueue_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkQueue_T(uint32_t familyIndex, float priority)
		:_queueFamilyIndex(familyIndex),_priority(priority)
	{
	}
	~VkQueue_T();

	uint32_t _queueFamilyIndex;
	float    _priority;

	void Push(vsrQueueJob* job);
	bool Empty();

	std::mutex               _listMutex;
	std::list<vsrQueueJob*>  _listJob;
};