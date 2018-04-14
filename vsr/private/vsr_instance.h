#pragma once

struct VkInstance_T :public MemoryAlloc<VkInstance_T, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE> {
	VkInstance_T();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;
};

