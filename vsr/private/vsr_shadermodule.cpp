#include "vsr_common.h"
#include "vsr_shadermodule.h"

VkAllocationCallbacks *MemoryAlloc<VkShaderModule_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkShaderModule_T::VkShaderModule_T(const VkShaderModuleCreateInfo* pCreateInfo)
{
	assert(pCreateInfo->codeSize % 4 == 0);
	_vecCodes.resize(pCreateInfo->codeSize / 4);
	std::memcpy(_vecCodes.data(), pCreateInfo->pCode, pCreateInfo->codeSize);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(
	VkDevice                                    device,
	const VkShaderModuleCreateInfo*             pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkShaderModule*                             pShaderModule)
{
	try
	{
		*pShaderModule = new(pAllocator) VkShaderModule_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(
	VkDevice                                    device,
	VkShaderModule                              shaderModule,
	const VkAllocationCallbacks*                pAllocator)
{
	delete shaderModule;
}