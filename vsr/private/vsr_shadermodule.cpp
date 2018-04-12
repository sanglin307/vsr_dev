#include "vsr_common.h"

VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(
	VkDevice                                    device,
	const VkShaderModuleCreateInfo*             pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkShaderModule*                             pShaderModule)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(
	VkDevice                                    device,
	VkShaderModule                              shaderModule,
	const VkAllocationCallbacks*                pAllocator)
{}