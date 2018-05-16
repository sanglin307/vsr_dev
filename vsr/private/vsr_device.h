#pragma once

struct VkDevice_T : public MemoryAlloc<VkDevice_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	VkResult init(VkPhysicalDevice physicalDevice,const VkDeviceCreateInfo* pCreateInfo,const VkAllocationCallbacks* pAllocator);
	~VkDevice_T();
	void Registe(vsrDeviceResource *res)
	{
		res->_device = this;
		_listResource.push_back(res);
	};

	void UnRegiste(vsrDeviceResource *res)
	{
		_listResource.remove(res);
	};

	std::map<std::string, PFN_vkVoidFunction>  _dispatchTable;
	std::vector<VkQueue>                       _vecQueues;
	VkPhysicalDevice                           _physicalDevice;

	std::list<vsrDeviceResource*>               _listResource;
};