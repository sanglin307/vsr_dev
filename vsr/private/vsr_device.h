#pragma once

#include <map>

struct VkDevice_T {
	void init();
	void exit();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;
};