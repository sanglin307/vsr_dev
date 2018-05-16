#include "vsr_common.h"
#include "vsr_descriptor.h"
#include "vsr_buffer.h"
#include "vsr_device.h"

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

	device->Registe(*pSampler);
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroySampler(
	VkDevice                                    device,
	VkSampler                                   sampler,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(sampler);
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

	device->Registe(*pSetLayout);
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(
	VkDevice                                    device,
	VkDescriptorSetLayout                       descriptorSetLayout,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(descriptorSetLayout);
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
	for (auto v : _descriptors)
	{
		delete v;
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
	for (auto v : _descriptors)
	{
		delete v;
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

	device->Registe(*pDescriptorPool);

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(
	VkDevice                                    device,
	VkDescriptorPool                            descriptorPool,
	const VkAllocationCallbacks*                pAllocator)
{
	device->UnRegiste(descriptorPool);

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
	for (uint32_t i = 0; i < layout->_vecBindings.size(); i++)
	{
		vkDescriptorObject obj;
		obj._binding = layout->_vecBindings[i].binding;
		obj._descriptorType = layout->_vecBindings[i].descriptorType;
		obj._count = layout->_vecBindings[i].descriptorCount;
		obj._pData = (vsrDescriptorDataType*)std::malloc(obj._count * sizeof(vsrDescriptorDataType));
		std::memset(obj._pData, 0, sizeof(vsrDescriptorDataType)*obj._count);
		if (obj._descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER || 
			obj._descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
		{
			if (layout->_vecBindings[i].pImmutableSamplers != nullptr)
			{
				for (uint32_t j = 0; j < layout->_vecBindings[i].descriptorCount; j++)
					obj._pData[j]._imageSampler._sampler = layout->_vecBindings[i].pImmutableSamplers[j];
			}
		}
		_vecDescriptors.push_back(obj);
	}
}

void VkDescriptorSet_T::Copy(const VkCopyDescriptorSet* pCopyInfo)
{
	vkDescriptorObject *pSrc = nullptr;
	vkDescriptorObject *pDst = nullptr;
	for (uint32_t j = 0; j < pCopyInfo->srcSet->_vecDescriptors.size(); j++)
	{
		if (pCopyInfo->srcSet->_vecDescriptors[j]._binding == pCopyInfo->srcBinding)
		{
			pSrc = &pCopyInfo->srcSet->_vecDescriptors[j];
			break;
		}
	}
	for (uint32_t j = 0; j < _vecDescriptors.size(); j++)
	{
		if (_vecDescriptors[j]._binding == pCopyInfo->dstBinding)
		{
			pDst = &_vecDescriptors[j];
			break;
		}
	}

	assert(pSrc != nullptr && pDst != nullptr);
	assert(pSrc->_descriptorType == pDst->_descriptorType);
	for (uint32_t j = 0; j < pCopyInfo->descriptorCount; j++)
	{
		if (pCopyInfo->srcArrayElement + j >= pSrc->_count)
			continue;
		if (pCopyInfo->dstArrayElement + j >= pDst->_count)
			continue;

		pDst->_pData[pCopyInfo->dstArrayElement + j] = pSrc->_pData[pCopyInfo->srcArrayElement + j];
	}
	 
}

void VkDescriptorSet_T::Write(const VkWriteDescriptorSet* pWriteInfo)
{
	for (auto& v : _vecDescriptors)
	{
		if (v._binding == pWriteInfo->dstBinding)
		{
			assert(v._descriptorType == pWriteInfo->descriptorType);
			if (v._descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER || v._descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
			{
				for (uint32_t i = pWriteInfo->dstArrayElement; i < pWriteInfo->dstArrayElement + pWriteInfo->descriptorCount && i < v._count; i++)
				{
					v._pData[i]._imageSampler._sampler = pWriteInfo->pImageInfo[i].sampler;
				}
			}

			if (v._descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
			{
				for (uint32_t i = pWriteInfo->dstArrayElement; i < pWriteInfo->dstArrayElement + pWriteInfo->descriptorCount && i < v._count; i++)
				{
					v._pData[i]._imageSampler._imageView = pWriteInfo->pImageInfo[i].imageView;
				}
			} else if (v._descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER)
			{
				for (uint32_t i = pWriteInfo->dstArrayElement; i < pWriteInfo->dstArrayElement + pWriteInfo->descriptorCount && i < v._count; i++)
					v._pData[i]._bufferTexView = pWriteInfo->pTexelBufferView[i];
			} else if (v._descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
				v._descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
			{
				for (uint32_t i = pWriteInfo->dstArrayElement; i < pWriteInfo->dstArrayElement + pWriteInfo->descriptorCount && i < v._count; i++)
				{
					v._pData[i]._buffer = (uint8_t*)pWriteInfo->pBufferInfo[i].buffer->_pData + pWriteInfo->pBufferInfo[i].offset;
				}
			}
			return;
		}
	}

	// not found£¡
	assert(0);
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
{
	for (uint32_t i = 0; i < descriptorWriteCount; i++)
	{
		pDescriptorWrites[i].dstSet->Write(&pDescriptorWrites[i]);
	}

	for (uint32_t i = 0; i < descriptorCopyCount; i++)
	{
		pDescriptorCopies[i].dstSet->Copy(&pDescriptorCopies[i]);
	}
}

