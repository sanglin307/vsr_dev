#pragma once

 

struct VkInstance_T {
	VkInstance_T();
	std::map<std::string, PFN_vkVoidFunction> _dispatchTable;

	void* operator new(size_t size, const VkAllocationCallbacks* pAllocator)
	{
		if (pAllocator != nullptr)
			return pAllocator->pfnAllocation(pAllocator->pUserData, size, Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE);
		else
			return std::malloc(size);
	}

	void operator delete(void *ptr, const VkAllocationCallbacks* pAllocator)
	{
		if (pAllocator != nullptr)
			pAllocator->pfnFree(pAllocator->pUserData, ptr);
		else
		{
			std::free(ptr);
		}
	}

};

