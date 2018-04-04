#include "vsr_common.h"
#include "vsr_queue.h"
#include "vsr_surface.h"
#include "vsr_physicaldevice.h"


VkPhysicalDevice_T* VkPhysicalDevice_T::_instance = nullptr;

VkPhysicalDevice_T::VkPhysicalDevice_T()
{
	vQueueFamily qf;
	qf._property.queueFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
	qf._property.queueCount = 16;
	qf._property.minImageTransferGranularity = { 1,1,1 };
	qf._property.timestampValidBits = 64;
	qf._supportSurface = 1,
	_vecQueueFamily.push_back(qf);
 
}

VkPhysicalDevice_T* VkPhysicalDevice_T::Get()
{
	if (_instance == nullptr)
	{
		_instance = new VkPhysicalDevice_T;
	}

	return _instance;
}

VkResult VkPhysicalDevice_T::GetPhysicalDeviceSurfaceSupportKHR(uint32_t queueFamilyIndex, VkSurfaceKHR  surface, VkBool32* pSupported)
{
	if (queueFamilyIndex < 0 || queueFamilyIndex >= _vecQueueFamily.size())
		return VK_ERROR_SURFACE_LOST_KHR;

	*pSupported = _vecQueueFamily[queueFamilyIndex]._supportSurface;
	return VK_SUCCESS;

}

void VkPhysicalDevice_T::GetPhysicalDeviceQueueFamilyProperties(
	uint32_t*                                   pQueueFamilyPropertyCount,
	VkQueueFamilyProperties*                    pQueueFamilyProperties)
{
	// use all in one first!
	*pQueueFamilyPropertyCount = (uint32_t)_vecQueueFamily.size();
	if (pQueueFamilyProperties == nullptr)
		return;

	for (size_t i = 0; i < _vecQueueFamily.size(); i++)
	{
		pQueueFamilyProperties[i] = _vecQueueFamily[i]._property;
	}
	
}

void VkPhysicalDevice_T::GetPhysicalDeviceFeatures(
	VkPhysicalDeviceFeatures*                   pFeatures)
{
	*pFeatures = Features;
}

void VkPhysicalDevice_T::GetPhysicalDeviceProperties(
	VkPhysicalDeviceProperties*                 pProperties)
{
	*pProperties = Properties;
}

void VkPhysicalDevice_T::GetPhysicalDeviceFormatProperties(
	VkFormat                                    format,
	VkFormatProperties*                         pFormatProperties)
{
	if (format > sizeof(FormatProperties) / sizeof(VkFormatProperties))
	{
		pFormatProperties->bufferFeatures = pFormatProperties->linearTilingFeatures = pFormatProperties->optimalTilingFeatures = 0;
	}
	else
	{
		*pFormatProperties = FormatProperties[format];
	}

}

void VkPhysicalDevice_T::GetPhysicalDeviceMemoryProperties(
	VkPhysicalDeviceMemoryProperties*           pMemoryProperties)
{
	pMemoryProperties->memoryHeapCount = 2;
	pMemoryProperties->memoryHeaps[0].size = 0x100000000; //4G
	pMemoryProperties->memoryHeaps[0].flags = VK_MEMORY_HEAP_DEVICE_LOCAL_BIT;

	pMemoryProperties->memoryHeaps[1].size = 0x100000000; //4G
	pMemoryProperties->memoryHeaps[1].flags = 0;  // host

	pMemoryProperties->memoryTypeCount = 2;
	pMemoryProperties->memoryTypes[0].heapIndex = 0;
	pMemoryProperties->memoryTypes[0].propertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	pMemoryProperties->memoryTypes[1].heapIndex = 1;
	pMemoryProperties->memoryTypes[1].propertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDevices(
	VkInstance                                  instance,
	uint32_t*                                   pPhysicalDeviceCount,
	VkPhysicalDevice*                           pPhysicalDevices)
{
	*pPhysicalDeviceCount = 1;
	if (pPhysicalDevices == nullptr)
		return VK_SUCCESS;

	*pPhysicalDevices = VkPhysicalDevice_T::Get();
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(
	VkPhysicalDevice                            physicalDevice,
	uint32_t*                                   pQueueFamilyPropertyCount,
	VkQueueFamilyProperties*                    pQueueFamilyProperties)
{
	return physicalDevice->GetPhysicalDeviceQueueFamilyProperties(pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures(
	VkPhysicalDevice                            physicalDevice,
	VkPhysicalDeviceFeatures*                   pFeatures)
{
	return physicalDevice->GetPhysicalDeviceFeatures(pFeatures);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties(
	VkPhysicalDevice                            physicalDevice,
	VkFormat                                    format,
	VkFormatProperties*                         pFormatProperties)
{
	return physicalDevice->GetPhysicalDeviceFormatProperties(format, pFormatProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(
	VkPhysicalDevice                            physicalDevice,
	VkPhysicalDeviceProperties*                 pProperties)
{
	return physicalDevice->GetPhysicalDeviceProperties(pProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties(
	VkPhysicalDevice                            physicalDevice,
	VkPhysicalDeviceMemoryProperties*           pMemoryProperties)
{
	return physicalDevice->GetPhysicalDeviceMemoryProperties(pMemoryProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceSupportKHR(
	VkPhysicalDevice                            physicalDevice,
	uint32_t                                    queueFamilyIndex,
	VkSurfaceKHR                                surface,
	VkBool32*                                   pSupported)
{
	return physicalDevice->GetPhysicalDeviceSurfaceSupportKHR(queueFamilyIndex, surface, pSupported);
}

