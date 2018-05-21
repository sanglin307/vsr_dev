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

	std::list<vsrDeviceResource*>              _listResource;
};

struct vsrStage {
	vsrStage();
	virtual ~vsrStage();
	virtual void Process() = 0;
	std::thread   *_pthread;
	std::atomic_bool _running;
};

struct vsrStage_InputAssemble : public vsrStage {
	vsrStage_InputAssemble();
	~vsrStage_InputAssemble();
	virtual void Process();
};

struct vsrStage_VertexShader : public vsrStage {
	vsrStage_VertexShader();
	virtual void Process();
};


struct vsrProcessor {
	vsrProcessor();
	~vsrProcessor();

	std::vector<vsrStage*>   _stages;
};