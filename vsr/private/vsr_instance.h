#pragma once

#include "../public/vulkan.h"
#include <map>

struct VkInstance_T {
	void init();
	void exit();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;
};

