#pragma once
 
struct vsrCommandInterface {
	virtual void Excute() = 0;
};


struct vsrCmd_Draw : public vsrCommandInterface {
	virtual void Excute();
	uint32_t                 _vertexCount;
	uint32_t                 _instanceCount;
	uint32_t                 _firstVertex;
	uint32_t                 _firstInstance;
};

struct vsrCmd_SetViewport : public vsrCommandInterface {
	virtual void Excute();
	uint32_t                  _firstViewport;
	std::vector<VkViewport>   _vecViewports;
};

struct vsrCmd_SetScissor : public vsrCommandInterface {
	virtual void Excute();
	uint32_t                  _firstScissor;
	std::vector<VkRect2D>     _vecScissors;
};

struct vsrCmd_CopyImage : public vsrCommandInterface {
	virtual void Excute();
	VkImage                   _srcImage;
	VkImageLayout             _srcImageLayout;
	VkImage                   _dstImage;
	VkImageLayout             _dstImageLayout;
	std::vector<VkImageCopy>  _vecRegions;
};

struct vsrCmd_BindPipeline : public vsrCommandInterface {
	virtual void Excute();
	VkPipelineBindPoint   _pipelineBindPoint;
    VkPipeline            _pipeline;
};

struct vsrCmd_BeginRenderPass : public vsrCommandInterface {
	virtual void Excute();
	VkSubpassContents           _contents;
	VkRenderPass                _renderPass;
	VkFramebuffer               _framebuffer;
	VkRect2D                    _renderArea;
	std::vector<VkClearValue>   _vecClearValues;
};

struct vsrCmd_EndRenderPass : public vsrCommandInterface {
	virtual void Excute();
};

struct vsrCmd_BindDescriptorSets : public vsrCommandInterface {
	virtual void Excute();
	VkPipelineBindPoint             _pipelineBindPoint;
	VkPipelineLayout                _layout;
	uint32_t                        _firstSet;
    std::vector<VkDescriptorSet>    _vecDescriptorSets;
	std::vector<uint32_t>           _vecDynamicOffsets;
};

enum vsrCommandBufferState {
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
	vsrCommandBufferState _state;
	VkCommandBufferLevel _level;
	std::list<vsrCommandInterface*> _listCommands;
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

