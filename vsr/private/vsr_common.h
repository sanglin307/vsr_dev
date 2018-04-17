#pragma once
#define NOMINMAX
#include <cassert>
#include <cstdlib>
#include <atomic>
#include <new>
#include <vector>
#include <map>
#include <algorithm>

#include "../public/vulkan.h"

#define Vk_Allocation_Alignment 64

 
template<typename T, VkSystemAllocationScope scope>
struct MemoryAlloc {
	static VkAllocationCallbacks *_pAllocator;
	static void* operator new(size_t size, const VkAllocationCallbacks* pAllocator)
	{
		_pAllocator = (VkAllocationCallbacks*)pAllocator;
		if (pAllocator != nullptr)
			return pAllocator->pfnAllocation(pAllocator->pUserData, size, Vk_Allocation_Alignment, scope);
		else
		{
			return std::malloc(size);
		}
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
		return operator delete(ptr);
	}
};

