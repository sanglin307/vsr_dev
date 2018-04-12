#pragma once

 

struct VkInstance_T {
	VkInstance_T();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;

	static VkAllocationCallbacks *_pAllocator;
	static void* operator new(size_t size, const VkAllocationCallbacks* pAllocator)
	{
		_pAllocator = (VkAllocationCallbacks*)pAllocator;
		if (pAllocator != nullptr)
			return pAllocator->pfnAllocation(pAllocator->pUserData, size, Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE);
		else
			return std::malloc(size);
	}

	static void operator delete(void *ptr)
	{
		if (_pAllocator != nullptr)
			_pAllocator->pfnFree(_pAllocator->pUserData, ptr);
		else
		{
			std::free(ptr);
		}
	}

	static void operator delete(void *ptr, const VkAllocationCallbacks* pAllocator)
	{
		return delete(ptr);
	}

};

