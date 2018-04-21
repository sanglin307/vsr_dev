#pragma once

enum vkCommandType {
	CT_CopyImage = 0,
};

struct vkCommandInterface {
	virtual void Excute() = 0;
};

struct vkCommand_CopyImage : public vkCommandInterface {
	virtual void Excute();
	VkImage                   _srcImage;
	VkImageLayout             _srcImageLayout;
	VkImage                   _dstImage;
	VkImageLayout             _dstImageLayout;
	std::vector<VkImageCopy>  _vecRegions;
};

enum vkCommandBufferState {
	CBS_Init = 0,
	CBS_Recording,
	CBS_Executable,
	CBS_Pending,
	CBS_Invalid,
};

struct VkCommandBuffer_T {
	VkCommandBuffer_T(VkCommandBufferLevel level)
		:_state(CBS_Init),_level(level)
	{}
	vkCommandBufferState _state;
	VkCommandBufferLevel _level;
	std::list<vkCommandInterface*> _listCommands;
};

struct VkCommandPool_T :  public MemoryAlloc<VkCommandPool_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkCommandPool_T(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo);
	VkDevice_T *_device;
	VkCommandPoolCreateFlags _flag;
	uint32_t  _queueFamilyIndex;
	std::vector<VkCommandBuffer_T*> _commandBuffers;
	VkResult Allocate(const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
	void Free(uint32_t commandBufferCount, const VkCommandBuffer*  pCommandBuffers);
};

