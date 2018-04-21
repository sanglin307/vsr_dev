#include "vsr_common.h"
#include "vsr_descriptor.h"

VkAllocationCallbacks *MemoryAlloc<VkSampler_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;

VkSampler_T::VkSampler_T(const VkSamplerCreateInfo* pCreateInfo)
{
	_magFilter = pCreateInfo->magFilter;
	_minFilter = pCreateInfo->minFilter;
	_mipmapMode = pCreateInfo->mipmapMode;
	_addressModeU = pCreateInfo->addressModeU;
	_addressModeV = pCreateInfo->addressModeV;
	_addressModeW = pCreateInfo->addressModeW;
	_mipLodBias = pCreateInfo->mipLodBias;
	_anisotropyEnable = pCreateInfo->anisotropyEnable;
	_maxAnisotropy = pCreateInfo->maxAnisotropy;
	_compareEnable = pCreateInfo->compareEnable;
	_compareOp = pCreateInfo->compareOp;
	_minLod = pCreateInfo->minLod;
	_maxLod = pCreateInfo->maxLod;
	_borderColor = pCreateInfo->borderColor;
	_unnormalizedCoordinates = pCreateInfo->unnormalizedCoordinates;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSampler(
	VkDevice                                    device,
	const VkSamplerCreateInfo*                  pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkSampler*                                  pSampler)
{
	try
	{
		*pSampler = new(pAllocator) VkSampler_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySampler(
	VkDevice                                    device,
	VkSampler                                   sampler,
	const VkAllocationCallbacks*                pAllocator)
{
	delete sampler;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
VkAllocationCallbacks *MemoryAlloc<VkDescriptorSetLayout_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;

VkDescriptorSetLayout_T::VkDescriptorSetLayout_T(const VkDescriptorSetLayoutCreateInfo* pCreateInfo)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(
	VkDevice                                    device,
	const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDescriptorSetLayout*                      pSetLayout)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(
	VkDevice                                    device,
	VkDescriptorSetLayout                       descriptorSetLayout,
	const VkAllocationCallbacks*                pAllocator)
{}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(
	VkDevice                                    device,
	const VkDescriptorPoolCreateInfo*           pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDescriptorPool*                           pDescriptorPool)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	const VkAllocationCallbacks*                pAllocator)
{}

VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	VkDescriptorPoolResetFlags                  flags)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(
	VkDevice                                    device,
	const VkDescriptorSetAllocateInfo*          pAllocateInfo,
	VkDescriptorSet*                            pDescriptorSets)
{
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	uint32_t                                    descriptorSetCount,
	const VkDescriptorSet*                      pDescriptorSets)
{
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(
	VkDevice                                    device,
	uint32_t                                    descriptorWriteCount,
	const VkWriteDescriptorSet*                 pDescriptorWrites,
	uint32_t                                    descriptorCopyCount,
	const VkCopyDescriptorSet*                  pDescriptorCopies)
{}

VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipelineLayout                            layout,
	uint32_t                                    firstSet,
	uint32_t                                    descriptorSetCount,
	const VkDescriptorSet*                      pDescriptorSets,
	uint32_t                                    dynamicOffsetCount,
	const uint32_t*                             pDynamicOffsets)
{}