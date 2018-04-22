#pragma once

struct VkPipelineLayout_T : public MemoryAlloc<VkPipelineLayout_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkPipelineLayout_T(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo);
	std::vector<VkDescriptorSetLayout>    _vecSetLayouts;
	std::vector<VkPushConstantRange>      _vecPushConstantRanges;
};

