#pragma once

struct VkShaderModule_T :public MemoryAlloc<VkShaderModule_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkShaderModule_T(const VkShaderModuleCreateInfo* pCreateInfo);
	std::vector<uint32_t>   _vecCodes;
};
