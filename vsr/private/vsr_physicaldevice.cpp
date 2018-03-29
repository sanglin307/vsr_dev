#include "vsr_define.h"
#include "vsr_physicaldevice.h"

VkPhysicalDevice_T* VkPhysicalDevice_T::_instance = nullptr;

VkPhysicalDevice_T* VkPhysicalDevice_T::Get()
{
	if (_instance == nullptr)
	{
		_instance = new VkPhysicalDevice_T;
	}

	return _instance;
}

void VkPhysicalDevice_T::GetPhysicalDeviceQueueFamilyProperties(
	uint32_t*                                   pQueueFamilyPropertyCount,
	VkQueueFamilyProperties*                    pQueueFamilyProperties)
{
	// use all in one first!
	*pQueueFamilyPropertyCount = 1;
	if (pQueueFamilyProperties == nullptr)
		return;

	pQueueFamilyProperties[0].queueFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
	pQueueFamilyProperties[0].queueCount = 1;
	pQueueFamilyProperties[0].minImageTransferGranularity = { 1,1,1 };
	pQueueFamilyProperties[0].timestampValidBits = 64;
}

void VkPhysicalDevice_T::GetPhysicalDeviceFeatures(
	VkPhysicalDeviceFeatures*                   pFeatures)
{
	*pFeatures = Features;
}

void VkPhysicalDevice_T::GetPhysicalDeviceProperties(
	VkPhysicalDeviceProperties*                 pProperties)
{

}

void VkPhysicalDevice_T::GetPhysicalDeviceFormatProperties(
	VkFormat                                    format,
	VkFormatProperties*                         pFormatProperties)
{

}

void VkPhysicalDevice_T::GetPhysicalDeviceMemoryProperties(
	VkPhysicalDeviceMemoryProperties*           pMemoryProperties)
{

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