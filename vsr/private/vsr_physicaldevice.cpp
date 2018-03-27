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

}