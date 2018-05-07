#pragma once
 
struct vkCommandInterface {
	virtual void Excute() = 0;
};

struct vkCmd_CopyImage : public vkCommandInterface {
	virtual void Excute();
	VkImage                   srcImage;
	VkImageLayout             srcImageLayout;
	VkImage                   dstImage;
	VkImageLayout             dstImageLayout;
	std::vector<VkImageCopy>  vecRegions;
};

struct vkCmd_BindPipeline : public vkCommandInterface {
	virtual void Excute();
	VkPipelineBindPoint   pipelineBindPoint;
    VkPipeline            pipeline;
};

struct vkCmd_BeginRenderPass : public vkCommandInterface {
	virtual void Excute();
	VkSubpassContents           contents;
	VkRenderPass                renderPass;
	VkFramebuffer               framebuffer;
	VkRect2D                    renderArea;
	std::vector<VkClearValue>   vecClearValues;
};

struct vkCmd_BindDescriptorSets : public vkCommandInterface {
	virtual void Excute();
	VkPipelineBindPoint             pipelineBindPoint;
	VkPipelineLayout                layout;
	uint32_t                        firstSet;
    std::vector<VkDescriptorSet>    vecDescriptorSets;
	std::vector<uint32_t>           vecDynamicOffsets;
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

