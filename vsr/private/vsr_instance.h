#pragma once

#include "../public/vulkan.h"
#include <map>

struct VkInstance_T {
	VkInstance_T();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;
};

