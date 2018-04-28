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

struct VkPipeline_T : public MemoryAlloc<VkPipeline_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkPipeline_T(VkDevice device,const VkGraphicsPipelineCreateInfo* pCreateInfos);
};
