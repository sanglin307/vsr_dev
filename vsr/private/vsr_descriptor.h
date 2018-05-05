#pragma once

struct VkSampler_T : public MemoryAlloc<VkSampler_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkSampler_T(const VkSamplerCreateInfo* pCreateInfo);

	VkFilter                _magFilter;
	VkFilter                _minFilter;
	VkSamplerMipmapMode     _mipmapMode;
	VkSamplerAddressMode    _addressModeU;
	VkSamplerAddressMode    _addressModeV;
	VkSamplerAddressMode    _addressModeW;
	float                   _mipLodBias;
	VkBool32                _anisotropyEnable;
	float                   _maxAnisotropy;
	VkBool32                _compareEnable;
	VkCompareOp             _compareOp;
	float                   _minLod;
	float                   _maxLod;
	VkBorderColor           _borderColor;
	VkBool32                _unnormalizedCoordinates;
};


struct VkDescriptorSetLayout_T : public MemoryAlloc<VkDescriptorSetLayout_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkDescriptorSetLayout_T(const VkDescriptorSetLayoutCreateInfo* pCreateInfo);
	std::vector<VkDescriptorSetLayoutBinding> _vecBindings;
};

struct VkDescriptorPool_T : public MemoryAlloc<VkDescriptorPool_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkDescriptorPool_T(const VkDescriptorPoolCreateInfo* pCreateInfo);
	~VkDescriptorPool_T();
	VkResult AllocateDescriptorSets(VkDevice device, uint32_t count, VkDescriptorSetLayout layout,VkDescriptorSet* pDescriptorSets);
	VkResult FreeDescriptorSets(uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets);
	VkResult ResetDescriptorPool(VkDevice device);

	VkDescriptorPoolCreateFlags    _flag;
	uint32_t                       _maxSets;
	std::vector<VkDescriptorPoolSize>    _vecPoolSizes;
	std::list<VkDescriptorSet>      _descriptors;
};

struct vkImageSamplerPack {
	VkSampler  _sampler;
	VkImageView _imageView;
};

union vkDescriptorDataType {
	vkImageSamplerPack _imageSampler;
	VkBufferView _bufferTexView;
	void*  _buffer;
};

struct vkDescriptorObject {
	~vkDescriptorObject()
	{
		if (_pData != nullptr)
		{
			std::free(_pData);
			_pData = nullptr;
		}
	}

	uint32_t               _binding;
	VkDescriptorType       _descriptorType;
	vkDescriptorDataType*  _pData;
	uint32_t               _count;
	
};

struct VkDescriptorSet_T  {
	VkDescriptorSet_T(VkDescriptorPool pool, VkDescriptorSetLayout layout);
	void Write(const VkWriteDescriptorSet* pWriteInfo);
	void Copy(const VkCopyDescriptorSet* pCopyInfo);
	std::vector<vkDescriptorObject> _vecDescriptors;
};