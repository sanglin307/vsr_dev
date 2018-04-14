#pragma once
 
struct VkDevice_T : public MemoryAlloc<VkDevice_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	VkResult init(VkPhysicalDevice physicalDevice,const VkDeviceCreateInfo* pCreateInfo,const VkAllocationCallbacks* pAllocator);
	~VkDevice_T();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;
	std::vector<VkQueue_T*> _vecQueues;
};