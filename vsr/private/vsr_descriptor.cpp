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
	for (uint32_t i = 0; i < pCreateInfo->bindingCount; i++)
	{
		_vecBindings.push_back(pCreateInfo->pBindings[i]);
	}
	
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(
	VkDevice                                    device,
	const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDescriptorSetLayout*                      pSetLayout)
{
	try
	{
		*pSetLayout = new(pAllocator) VkDescriptorSetLayout_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(
	VkDevice                                    device,
	VkDescriptorSetLayout                       descriptorSetLayout,
	const VkAllocationCallbacks*                pAllocator)
{
	delete descriptorSetLayout;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

VkAllocationCallbacks *MemoryAlloc<VkDescriptorPool_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkDescriptorPool_T::VkDescriptorPool_T(const VkDescriptorPoolCreateInfo* pCreateInfo)
	:_flag(pCreateInfo->flags), _maxSets(pCreateInfo->maxSets)
{
	for (uint32_t i = 0; i < pCreateInfo->poolSizeCount; i++)
	{
		_vecPoolSizes.push_back(pCreateInfo->pPoolSizes[i]);
	}
}

VkDescriptorPool_T::~VkDescriptorPool_T()
{
	for (auto iter = _descriptors.begin(); iter != _descriptors.end(); ++iter)
	{
		delete *iter;
	}
	_descriptors.clear();
}

VkResult VkDescriptorPool_T::AllocateDescriptorSets(VkDevice device, uint32_t count, VkDescriptorSetLayout layout,VkDescriptorSet* pDescriptorSets)
{
	for (uint32_t i = 0; i < count; i++)
	{
		VkDescriptorSet_T *pSet = new VkDescriptorSet_T(this, layout);
		_descriptors.push_back(pSet);
		pDescriptorSets[i] = pSet;
	}
	return VK_SUCCESS;
}

VkResult VkDescriptorPool_T::ResetDescriptorPool(VkDevice device)
{
	for (auto iter = _descriptors.begin(); iter != _descriptors.end(); ++iter)
	{
		delete *iter;
	}
	_descriptors.clear();
	return VK_SUCCESS;
}

VkResult VkDescriptorPool_T::FreeDescriptorSets(uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
	for (uint32_t i = 0; i < descriptorSetCount; i++)
	{
		_descriptors.remove(pDescriptorSets[i]);
		delete pDescriptorSets[i];
	}
	return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(
	VkDevice                                    device,
	const VkDescriptorPoolCreateInfo*           pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDescriptorPool*                           pDescriptorPool)
{
	try
	{
		*pDescriptorPool = new(pAllocator) VkDescriptorPool_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	const VkAllocationCallbacks*                pAllocator)
{
	delete descriptorPool;
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	VkDescriptorPoolResetFlags                  flags)
{
	return descriptorPool->ResetDescriptorPool(device);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
VkDescriptorSet_T::VkDescriptorSet_T(VkDescriptorPool pool, VkDescriptorSetLayout layout)
{
	_pool = pool;
	_layout = layout;
}

VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(
	VkDevice                                    device,
	const VkDescriptorSetAllocateInfo*          pAllocateInfo,
	VkDescriptorSet*                            pDescriptorSets)
{
	return pAllocateInfo->descriptorPool->AllocateDescriptorSets(device, pAllocateInfo->descriptorSetCount, *pAllocateInfo->pSetLayouts,pDescriptorSets);
}

VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	uint32_t                                    descriptorSetCount,
	const VkDescriptorSet*                      pDescriptorSets)
{
	return descriptorPool->FreeDescriptorSets(descriptorSetCount, pDescriptorSets);
}

VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(
	VkDevice                                    device,
	uint32_t                                    descriptorWriteCount,
	const VkWriteDescriptorSet*                 pDescriptorWrites,
	uint32_t                                    descriptorCopyCount,
	const VkCopyDescriptorSet*                  pDescriptorCopies)
{}

