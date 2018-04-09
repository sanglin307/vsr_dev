#include "vsr_common.h"
#include "vsr_instance.h"

VkInstance_T::VkInstance_T()
{
	_dispatchTable["vkDestroyInstance"] = (PFN_vkVoidFunction)vkDestroyInstance;
	_dispatchTable["vkGetDeviceProcAddr"] = (PFN_vkVoidFunction)vkGetDeviceProcAddr;
	_dispatchTable["vkCreateDevice"] = (PFN_vkVoidFunction)vkCreateDevice;

	_dispatchTable["vkEnumeratePhysicalDevices"] = (PFN_vkVoidFunction)vkEnumeratePhysicalDevices;
	_dispatchTable["vkGetPhysicalDeviceQueueFamilyProperties"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceQueueFamilyProperties;
	_dispatchTable["vkGetPhysicalDeviceFeatures"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceFeatures;
	_dispatchTable["vkGetPhysicalDeviceFormatProperties"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceFormatProperties;
	_dispatchTable["vkGetPhysicalDeviceProperties"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceProperties;
	_dispatchTable["vkGetPhysicalDeviceMemoryProperties"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceMemoryProperties;

	_dispatchTable["vkGetPhysicalDeviceSurfaceSupportKHR"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceSurfaceSupportKHR;
	_dispatchTable["vkGetPhysicalDeviceSurfaceFormatsKHR"] = (PFN_vkVoidFunction)vkGetPhysicalDeviceSurfaceFormatsKHR;
}
 

VKAPI_ATTR VkResult VKAPI_PTR vkCreateInstance(
	const VkInstanceCreateInfo*                 pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkInstance*                                 pInstance)
{

	VkInstance_T *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = (VkInstance_T*)pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkInstance_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE);
	}
	else
	{
		pMem = (VkInstance_T*)std::malloc(sizeof(VkInstance_T));
	}
	
	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	*pInstance = new(pMem) VkInstance_T;

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
	*pApiVersion = VK_API_VERSION_1_0;
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(
	const char*                                 pLayerName,
	uint32_t*                                   pPropertyCount,
	VkExtensionProperties*                      pProperties)
{
	//surface extension must support!
	//hardcode!
	*pPropertyCount = 2;
	if (pProperties == nullptr)
		return VK_SUCCESS;

	pProperties[0].specVersion = VK_VERSION_1_1;
	std::strcpy(pProperties[0].extensionName , VK_KHR_SURFACE_EXTENSION_NAME);

#if VK_USE_PLATFORM_WIN32_KHR
	pProperties[1].specVersion = VK_VERSION_1_1;
	std::strcpy(pProperties[1].extensionName , VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

	return VK_SUCCESS;

}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(
	uint32_t*                                   pPropertyCount,
	VkLayerProperties*                          pProperties)
{
	*pPropertyCount = 0;
	return VK_SUCCESS;
}


VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(
	VkInstance                                  instance,
	const char*                                 pName)
{

	if (std::strcmp(pName, "vkEnumerateInstanceVersion") == 0)
		return (PFN_vkVoidFunction)vkEnumerateInstanceVersion;
 
	if (std::strcmp(pName, "vkEnumerateInstanceLayerProperties") == 0)
		return (PFN_vkVoidFunction)vkEnumerateInstanceLayerProperties;

	if (std::strcmp(pName, "vkEnumerateInstanceExtensionProperties") == 0)
		return (PFN_vkVoidFunction)vkEnumerateInstanceExtensionProperties;

	if (std::strcmp(pName, "vkCreateInstance") == 0)
		return (PFN_vkVoidFunction)vkCreateInstance;

	auto iter = instance->_dispatchTable.find(pName);
	if (iter == instance->_dispatchTable.end())
		return nullptr;
	else
		return iter->second;
}