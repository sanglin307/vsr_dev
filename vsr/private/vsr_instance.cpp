#include "vsr_define.h"
#include "vsr_instance.h"

VkInstance_T::VkInstance_T()
{
	_dispatchTable["vkCreateInstance"] = (PFN_vkVoidFunction)vkCreateInstance;
	_dispatchTable["vkDestroyInstance"] = (PFN_vkVoidFunction)vkDestroyInstance;

	_dispatchTable["vkEnumeratePhysicalDevices"] = (PFN_vkVoidFunction)vkEnumeratePhysicalDevices;
}

VKAPI_ATTR VkResult VKAPI_PTR vkCreateInstance(
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

VKAPI_ATTR void VKAPI_PTR vkDestroyInstance(
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

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceVersion(
	uint32_t*                                   pApiVersion)
{
	*pApiVersion = 
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(
	VkInstance                                  instance,
	const char*                                 pName)
{

	if(strcmp(pName,"vkEnumerateInstanceVersion") == 0)


		fp

		NULL

		vkEnumerateInstanceExtensionProperties

		fp

		NULL

		vkEnumerateInstanceLayerProperties

		fp

		NULL

		vkCreateInstance
	auto iter = instance->_dispatchTable.find(pName);
	if (iter == instance->_dispatchTable.end())
		return nullptr;
	else
		return iter->second;
}