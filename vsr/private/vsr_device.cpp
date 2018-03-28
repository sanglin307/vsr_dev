#include "vsr_define.h"
#include "vsr_device.h"

void VkDevice_T::init()
{
	_dispatchTable["vkDestroyDevice"] = (PFN_vkVoidFunction)vkDestroyDevice;
	_dispatchTable["vkEnumerateDeviceExtensionProperties"] = (PFN_vkVoidFunction)vkEnumerateDeviceExtensionProperties;
	_dispatchTable["vkEnumerateDeviceLayerProperties"] = (PFN_vkVoidFunction)vkEnumerateDeviceLayerProperties;
}

void VkDevice_T::exit()
{
	_dispatchTable.clear();
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(
	VkPhysicalDevice                            physicalDevice,
	const VkDeviceCreateInfo*                   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDevice*                                   pDevice)
{
	void *pMem = nullptr;
	if (pAllocator != nullptr)
	{
		pMem = pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkDevice_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
	}
	else
	{
		pMem = std::malloc(sizeof(VkDevice_T));
	}

	if (pMem == nullptr)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	*pDevice = (VkDevice_T *)pMem;
	(*pDevice)->init();

	return VK_SUCCESS;
}


VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(
	VkDevice                                    device,
	const VkAllocationCallbacks*                pAllocator)
{
	device->exit();
	if (pAllocator != nullptr)
	{
		pAllocator->pfnFree(pAllocator->pUserData, device);
	}
	else
	{
		std::free(device);
	}

}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(
	VkPhysicalDevice                            physicalDevice,
	const char*                                 pLayerName,
	uint32_t*                                   pPropertyCount,
	VkExtensionProperties*                      pProperties)
{
	//hard code
	*pPropertyCount = 1;
	pProperties[0].specVersion = VK_VERSION_1_1;
	std::strcpy(pProperties[0].extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME);
	return VK_SUCCESS;

}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(
	VkPhysicalDevice                            physicalDevice,
	uint32_t*                                   pPropertyCount,
	VkLayerProperties*                          pProperties)
{
	*pPropertyCount = 0;
	return VK_SUCCESS;
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(
	VkDevice                                    device,
	const char*                                 pName)
{
	if (device == nullptr)
		return nullptr;

	auto iter = device->_dispatchTable.find(pName);
	if (iter == device->_dispatchTable.end())
		return nullptr;
	else
		return iter->second;
}