#include "vsr_define.h"
#include "vsr_instance.h"

VkResult vkCreateInstance(
	const VkInstanceCreateInfo*                 pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkInstance*                                 pInstance)
{

	void *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkInstance_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE);
	}
	else
	{
		pMem = std::malloc(sizeof(VkInstance_T));
	}
	
	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	*pInstance = (VkInstance_T *)pMem;

	return VK_SUCCESS;
}

void  vkDestroyInstance(
	VkInstance                                  instance,
	const VkAllocationCallbacks*                pAllocator)
{
	if (pAllocator != nullptr)
	{
		pAllocator->pfnFree(pAllocator->pUserData, instance);
	}
	else
	{
		std::free(instance);
	}
}