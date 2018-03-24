#include "vsr_instance.h"
#include "vsr_physicaldevice.h"

#include "../public/vsr_queue.h"
#include "../public/vsr_physicaldevice.h"

extern VkPhysicalDevice_T GPhysicalDevice;

VkResult vkEnumeratePhysicalDevices(
	VkInstance                                  instance,
	uint32_t*                                   pPhysicalDeviceCount,
	VkPhysicalDevice*                           pPhysicalDevices)
{
	*pPhysicalDeviceCount = 1;
	if (pPhysicalDevices == nullptr)
		return VK_SUCCESS;

	*pPhysicalDevices = &GPhysicalDevice;
	return VK_SUCCESS;
}

void vkGetPhysicalDeviceQueueFamilyProperties(
	VkPhysicalDevice                            physicalDevice,
	uint32_t*                                   pQueueFamilyPropertyCount,
	VkQueueFamilyProperties*                    pQueueFamilyProperties)
{

}