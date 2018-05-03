#pragma once

struct VkPipelineLayout_T : public MemoryAlloc<VkPipelineLayout_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkPipelineLayout_T(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo);
	std::vector<VkDescriptorSetLayout>    _vecSetLayouts;
	std::vector<VkPushConstantRange>      _vecPushConstantRanges;
};


struct VkPipelineCache_T : public MemoryAlloc<VkPipelineCache_T, VK_SYSTEM_ALLOCATION_SCOPE_CACHE> {
	VkPipelineCache_T(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo);
	std::vector<uint8_t> _vecData;
};

#define VK_ShaderStageNameLength    64  
struct vkShaderStage {
	VkShaderStageFlagBits               _stage;
	std::vector<uint32_t>               _code;
	char                                _name[VK_ShaderStageNameLength];
	std::vector<VkSpecializationMapEntry>  _vecMapEntries;
	size_t                             _dataSize;
	const void*                        _pData;
};

struct VkPipeline_T : public MemoryAlloc<VkPipeline_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkPipeline_T(VkDevice device,const VkGraphicsPipelineCreateInfo* pCreateInfos);

	VkPipelineCreateFlags                           _flags;
	VkPrimitiveTopology                             _topology;
	VkBool32                                        _primitiveRestartEnable;
	uint32_t                                        _patchControlPoints;      // tessellation stage

	// rasterization
	VkBool32                                        _depthClampEnable;
	VkBool32                                        _rasterizerDiscardEnable;
	VkPolygonMode                                   _polygonMode;
	VkCullModeFlags                                 _cullMode;
	VkFrontFace                                     _frontFace;
	VkBool32                                        _depthBiasEnable;
	float                                           _depthBiasConstantFactor;
	float                                           _depthBiasClamp;
	float                                           _depthBiasSlopeFactor;
	float                                           _lineWidth;

	//multisample
	VkSampleCountFlagBits                           _rasterizationSamples;
	VkBool32                                        _sampleShadingEnable;
	float                                           _minSampleShading;
	//const VkSampleMask*                             _pSampleMask;
	VkBool32                                        _alphaToCoverageEnable;
	VkBool32                                        _alphaToOneEnable;

	//depth stencil
	VkBool32                                        _depthTestEnable;
	VkBool32                                        _depthWriteEnable;
	VkCompareOp                                     _depthCompareOp;
	VkBool32                                        _depthBoundsTestEnable;
	VkBool32                                        _stencilTestEnable;
	VkStencilOpState                                _front;
	VkStencilOpState                                _back;
	float                                           _minDepthBounds;
	float                                           _maxDepthBounds;

	//blend
	VkBool32                                        _blendLogicOpEnable;
	VkLogicOp                                       _blendLogicOp;
	std::vector<VkPipelineColorBlendAttachmentState>    _vecBlendAttachments;
	float                                           _blendConstants[4];
 
	std::vector<VkDynamicState>                     _vecDynamicStates;
	std::vector<VkViewport>                         _vecViewports;
	std::vector<VkRect2D>                           _vecScissors;
	std::vector<vkShaderStage>                      _vecStages;
	std::vector<VkVertexInputBindingDescription>    _vecVertexBindingDescriptions;
	std::vector<VkVertexInputAttributeDescription>  _vecVertexAttributeDescriptions;

	VkPipelineLayout                                 _layout;
	VkRenderPass                                     _renderPass;
	uint32_t                                         _subpass;
};
