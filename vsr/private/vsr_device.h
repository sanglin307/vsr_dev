#pragma once
 

struct VkDevice_T {
	VkResult init(VkPhysicalDevice physicalDevice,const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator);
	void exit(const VkAllocationCallbacks* pAllocator);
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;
	std::vector<VkQueue_T*> _vecQueues;
};