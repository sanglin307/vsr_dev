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