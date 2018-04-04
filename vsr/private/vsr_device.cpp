#include "vsr_common.h"
#include "vsr_queue.h"
#include "vsr_physicaldevice.h"
#include "vsr_device.h"


#include <algorithm>

VkResult VkDevice_T::init(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator)
{
	_dispatchTable["vkDestroyDevice"] = (PFN_vkVoidFunction)vkDestroyDevice;
	_dispatchTable["vkEnumerateDeviceExtensionProperties"] = (PFN_vkVoidFunction)vkEnumerateDeviceExtensionProperties;
	_dispatchTable["vkEnumerateDeviceLayerProperties"] = (PFN_vkVoidFunction)vkEnumerateDeviceLayerProperties;
	_dispatchTable["vkGetDeviceQueue"] = (PFN_vkVoidFunction)vkGetDeviceQueue;

	_dispatchTable["vkCreateSwapchainKHR"] = (PFN_vkVoidFunction)vkCreateSwapchainKHR;
	_dispatchTable["vkDestroySwapchainKHR"] = (PFN_vkVoidFunction)vkDestroySwapchainKHR;
	_dispatchTable["vkGetSwapchainImagesKHR"] = (PFN_vkVoidFunction)vkGetSwapchainImagesKHR;
	_dispatchTable["vkAcquireNextImageKHR"] = (PFN_vkVoidFunction)vkAcquireNextImageKHR;
	_dispatchTable["vkQueuePresentKHR"] = (PFN_vkVoidFunction)vkQueuePresentKHR;

	for (uint32_t i = 0; i < pCreateInfo->queueCreateInfoCount; i++)
	{
		if (pCreateInfo->pQueueCreateInfos[i].queueFamilyIndex >= physicalDevice->_vecQueueFamily.size())
			return VK_ERROR_INITIALIZATION_FAILED;

		for (uint32_t j = 0; j < pCreateInfo->pQueueCreateInfos[i].queueCount; j++)
		{
			VkQueue_T *pMem = nullptr;
			if (pAllocator != nullptr)
				pMem = (VkQueue_T*)pAllocator->pfnAllocation(pAllocator->pUserData, sizeof(VkQueue_T), Vk_Allocation_Alignment, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE);
			else
				pMem = (VkQueue_T*)std::malloc(sizeof(VkQueue_T));

			if (pMem == nullptr)
				return VK_ERROR_OUT_OF_HOST_MEMORY;

			pMem->_queueFamilyIndex = pCreateInfo->pQueueCreateInfos[i].queueFamilyIndex;
			pMem->_priority = pCreateInfo->pQueueCreateInfos[i].pQueuePriorities[j];
			_vecQueues.push_back(pMem);
		}
	}

	std::sort(_vecQueues.begin(), _vecQueues.end(), [](VkQueue_T* q1, VkQueue_T*q2) 
	{
		if (q1->_queueFamilyIndex < q2->_queueFamilyIndex)
			return true;
		else if (q1->_queueFamilyIndex == q2->_queueFamilyIndex)
		{
			return q1->_priority > q2->_priority;
		}
		else
			return false;
	});

	return VK_SUCCESS;

}

void VkDevice_T::exit(const VkAllocationCallbacks* pAllocator)
{
	if (pAllocator != nullptr)
	{
		for (int i = 0; i < _vecQueues.size(); i++)
		{
			pAllocator->pfnFree(pAllocator->pUserData, _vecQueues[i]);
		}
	}
	else
	{
		for (int i = 0; i < _vecQueues.size(); i++)
		{
			std::free(_vecQueues[i]);
		}
	}

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
	VkResult res = (*pDevice)->init(physicalDevice,pCreateInfo,pAllocator);
	if (res != VK_SUCCESS)
	{
		vkDestroyDevice(*pDevice, pAllocator);
		return res;
	}

	return VK_SUCCESS;
}


VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(
	VkDevice                                    device,
	const VkAllocationCallbacks*                pAllocator)
{
	device->exit(pAllocator);
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

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue(
	VkDevice                                    device,
	uint32_t                                    queueFamilyIndex,
	uint32_t                                    queueIndex,
	VkQueue*                                    pQueue)
{
	int index = -1;
	for (size_t i = 0; i < device->_vecQueues.size(); i++)
	{
		if (device->_vecQueues[i]->_queueFamilyIndex == queueFamilyIndex)
		{
			if (index == -1)
				index = 0;
			else
				index++;

			if (index == queueIndex)
			{
				*pQueue = device->_vecQueues[i];
				break;
			}
		}

	}
}