#include "vsr_common.h"
#include "vsr_physicaldevice.h"
#include "vsr_device.h"
#include <algorithm>

VkAllocationCallbacks *MemoryAlloc<VkDevice_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE>::_pAllocator = nullptr;
VkResult VkDevice_T::init(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator)
{
	_physicalDevice = physicalDevice;

	_dispatchTable["vkDestroyDevice"] = (PFN_vkVoidFunction)vkDestroyDevice;
	_dispatchTable["vkEnumerateDeviceExtensionProperties"] = (PFN_vkVoidFunction)vkEnumerateDeviceExtensionProperties;
	_dispatchTable["vkEnumerateDeviceLayerProperties"] = (PFN_vkVoidFunction)vkEnumerateDeviceLayerProperties;
	_dispatchTable["vkGetDeviceQueue"] = (PFN_vkVoidFunction)vkGetDeviceQueue;
	_dispatchTable["vkDeviceWaitIdle"] = (PFN_vkVoidFunction)vkDeviceWaitIdle;
	_dispatchTable["vkAllocateMemory"] = (PFN_vkVoidFunction)vkAllocateMemory;
	_dispatchTable["vkFreeMemory"] = (PFN_vkVoidFunction)vkFreeMemory;
	_dispatchTable["vkMapMemory"] = (PFN_vkVoidFunction)vkMapMemory;
	_dispatchTable["vkUnmapMemory"] = (PFN_vkVoidFunction)vkUnmapMemory;
	_dispatchTable["vkBindBufferMemory"] = (PFN_vkVoidFunction)vkBindBufferMemory;
	_dispatchTable["vkBindImageMemory"] = (PFN_vkVoidFunction)vkBindImageMemory;
	_dispatchTable["vkCreateFence"] = (PFN_vkVoidFunction)vkCreateFence;
	_dispatchTable["vkDestroyFence"] = (PFN_vkVoidFunction)vkDestroyFence;
	_dispatchTable["vkResetFences"] = (PFN_vkVoidFunction)vkResetFences;
	_dispatchTable["vkWaitForFences"] = (PFN_vkVoidFunction)vkWaitForFences;
	_dispatchTable["vkCreateSemaphore"] = (PFN_vkVoidFunction)vkCreateSemaphore;
	_dispatchTable["vkDestroySemaphore"] = (PFN_vkVoidFunction)vkDestroySemaphore;
	_dispatchTable["vkCreateCommandPool"] = (PFN_vkVoidFunction)vkCreateCommandPool;
	_dispatchTable["vkDestroyCommandPool"] = (PFN_vkVoidFunction)vkDestroyCommandPool;
	_dispatchTable["vkResetCommandPool"] = (PFN_vkVoidFunction)vkResetCommandPool;
	_dispatchTable["vkFreeCommandBuffers"] = (PFN_vkVoidFunction)vkFreeCommandBuffers;
	_dispatchTable["vkAllocateCommandBuffers"] = (PFN_vkVoidFunction)vkAllocateCommandBuffers;
	_dispatchTable["vkBeginCommandBuffer"] = (PFN_vkVoidFunction)vkBeginCommandBuffer;
	_dispatchTable["vkEndCommandBuffer"] = (PFN_vkVoidFunction)vkEndCommandBuffer;
	_dispatchTable["vkGetImageMemoryRequirements"] = (PFN_vkVoidFunction)vkGetImageMemoryRequirements;
	_dispatchTable["vkCreateImage"] = (PFN_vkVoidFunction)vkCreateImage;
	_dispatchTable["vkDestroyImage"] = (PFN_vkVoidFunction)vkDestroyImage;
	_dispatchTable["vkGetImageSubresourceLayout"] = (PFN_vkVoidFunction)vkGetImageSubresourceLayout;
	_dispatchTable["vkCreateImageView"] = (PFN_vkVoidFunction)vkCreateImageView;
	_dispatchTable["vkDestroyImageView"] = (PFN_vkVoidFunction)vkDestroyImageView;
	_dispatchTable["vkCmdCopyImage"] = (PFN_vkVoidFunction)vkCmdCopyImage;
	_dispatchTable["vkCreateSampler"] = (PFN_vkVoidFunction)vkCreateSampler;
	_dispatchTable["vkDestroySampler"] = (PFN_vkVoidFunction)vkDestroySampler;
	_dispatchTable["vkCreateBuffer"] = (PFN_vkVoidFunction)vkCreateBuffer;
	_dispatchTable["vkDestroyBuffer"] = (PFN_vkVoidFunction)vkDestroyBuffer;
	_dispatchTable["vkGetBufferMemoryRequirements"] = (PFN_vkVoidFunction)vkGetBufferMemoryRequirements;
	_dispatchTable["vkCreateDescriptorSetLayout"] = (PFN_vkVoidFunction)vkCreateDescriptorSetLayout;
	_dispatchTable["vkDestroyDescriptorSetLayout"] = (PFN_vkVoidFunction)vkDestroyDescriptorSetLayout;
	_dispatchTable["vkCreateDescriptorPool"] = (PFN_vkVoidFunction)vkCreateDescriptorPool;
	_dispatchTable["vkDestroyDescriptorPool"] = (PFN_vkVoidFunction)vkDestroyDescriptorPool;
	_dispatchTable["vkResetDescriptorPool"] = (PFN_vkVoidFunction)vkResetDescriptorPool;
	_dispatchTable["vkAllocateDescriptorSets"] = (PFN_vkVoidFunction)vkAllocateDescriptorSets;
	_dispatchTable["vkFreeDescriptorSets"] = (PFN_vkVoidFunction)vkFreeDescriptorSets;
	_dispatchTable["vkUpdateDescriptorSets"] = (PFN_vkVoidFunction)vkUpdateDescriptorSets;
	_dispatchTable["vkCmdBindDescriptorSets"] = (PFN_vkVoidFunction)vkCmdBindDescriptorSets;
	_dispatchTable["vkCreatePipelineLayout"] = (PFN_vkVoidFunction)vkCreatePipelineLayout;
	_dispatchTable["vkDestroyPipelineLayout"] = (PFN_vkVoidFunction)vkDestroyPipelineLayout;
	_dispatchTable["vkDestroyPipeline"] = (PFN_vkVoidFunction)vkDestroyPipeline;
	_dispatchTable["vkCreateComputePipelines"] = (PFN_vkVoidFunction)vkCreateComputePipelines;
	_dispatchTable["vkCreateGraphicsPipelines"] = (PFN_vkVoidFunction)vkCreateGraphicsPipelines;
	_dispatchTable["vkMergePipelineCaches"] = (PFN_vkVoidFunction)vkMergePipelineCaches;
	_dispatchTable["vkGetPipelineCacheData"] = (PFN_vkVoidFunction)vkGetPipelineCacheData;
	_dispatchTable["vkDestroyPipelineCache"] = (PFN_vkVoidFunction)vkDestroyPipelineCache;
	_dispatchTable["vkCreatePipelineCache"] = (PFN_vkVoidFunction)vkCreatePipelineCache;

	_dispatchTable["vkCreateRenderPass"] = (PFN_vkVoidFunction)vkCreateRenderPass;
	_dispatchTable["vkDestroyRenderPass"] = (PFN_vkVoidFunction)vkDestroyRenderPass;
	_dispatchTable["vkCreateFramebuffer"] = (PFN_vkVoidFunction)vkCreateFramebuffer;
	_dispatchTable["vkDestroyFramebuffer"] = (PFN_vkVoidFunction)vkDestroyFramebuffer;

	_dispatchTable["vkCmdBindPipeline"] = (PFN_vkVoidFunction)vkCmdBindPipeline;
	_dispatchTable["vkCmdCopyImage"] = (PFN_vkVoidFunction)vkCmdCopyImage;
	_dispatchTable["vkCmdBeginRenderPass"] = (PFN_vkVoidFunction)vkCmdBeginRenderPass;
	_dispatchTable["vkCmdNextSubpass"] = (PFN_vkVoidFunction)vkCmdNextSubpass;
	_dispatchTable["vkCmdBindDescriptorSets"] = (PFN_vkVoidFunction)vkCmdBindDescriptorSets;
	
	_dispatchTable["vkCreateSwapchainKHR"] = (PFN_vkVoidFunction)vkCreateSwapchainKHR;
	_dispatchTable["vkDestroySwapchainKHR"] = (PFN_vkVoidFunction)vkDestroySwapchainKHR;
	_dispatchTable["vkGetSwapchainImagesKHR"] = (PFN_vkVoidFunction)vkGetSwapchainImagesKHR;
	_dispatchTable["vkAcquireNextImageKHR"] = (PFN_vkVoidFunction)vkAcquireNextImageKHR;
	_dispatchTable["vkQueuePresentKHR"] = (PFN_vkVoidFunction)vkQueuePresentKHR;

	for (uint32_t i = 0; i < pCreateInfo->queueCreateInfoCount; i++)
	{
		if (pCreateInfo->pQueueCreateInfos[i].queueFamilyIndex >= physicalDevice->_vecQueueFamily.size())
			return VK_ERROR_INITIALIZATION_FAILED;

		VkQueue_T *pQueue = nullptr;
		for (uint32_t j = 0; j < pCreateInfo->pQueueCreateInfos[i].queueCount; j++)
		{
			pQueue = new (pAllocator) VkQueue_T(pCreateInfo->pQueueCreateInfos[i].queueFamilyIndex, pCreateInfo->pQueueCreateInfos[i].pQueuePriorities[j]);
			_vecQueues.push_back(pQueue);
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

VkDevice_T::~VkDevice_T()
{
	for (auto v : _listResource)
		delete v;

	for (auto v : _vecQueues)
		delete v;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(
	VkPhysicalDevice                            physicalDevice,
	const VkDeviceCreateInfo*                   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDevice*                                   pDevice)
{
	try
	{
		*pDevice = new(pAllocator) VkDevice_T;
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	VkResult res = (*pDevice)->init(physicalDevice,pCreateInfo,pAllocator);
	if (res != VK_SUCCESS)
	{
		delete (*pDevice);
		return res;
	}
 
	return VK_SUCCESS;
}


VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(
	VkDevice                                    device,
	const VkAllocationCallbacks*                pAllocator)
{
	delete device;
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

VKAPI_ATTR VkResult VKAPI_CALL vkDeviceWaitIdle(
	VkDevice                                    device)
{
	return VK_SUCCESS;
}