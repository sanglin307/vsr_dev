#pragma once

struct VkImage_T : public MemoryAlloc<VkImage_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkImage_T(VkImageType type,VkFormat format,VkExtent3D extent,uint32_t arrayLayers,VkImageTiling tiling,VkImageUsageFlags usage,VkSharingMode sharingMode,
		      uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices, VkImageLayout layout);
	VkImage_T(const VkImageCreateInfo *pCreateInfo);
	~VkImage_T();

	void GetImageMemoryRequirements(VkDevice device, VkMemoryRequirements* pMemoryRequirements);
	void BindMemory(void* pData)
	{
		assert(_pData == nullptr);
		_pData = pData;
	}

	static uint32_t GetImageComponentSize(VkFormat format);
	static uint32_t GetImageComponentNum(VkFormat format);
	static bool IsDepthStencilFormat(VkFormat format);
	static uint32_t GetDepthStencilFormatSize(VkFormat format);

	VkImageType                      _type;
	VkFormat                         _format;
	VkExtent3D                       _extent;
	uint32_t                         _arrayLayers;
	VkImageUsageFlags                _usage;
	VkSharingMode                    _sharingMode;
	std::vector<uint32_t>            _vecQueueFamilyIndices;
	VkImageLayout                    _layout;
	VkImageTiling                    _tiling;

	VkDeviceSize                     _size;
	void*                            _pData;
};

struct VkImageView_T : public MemoryAlloc<VkImageView_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkImageView_T(const VkImageViewCreateInfo* pCreateInfo);

	static bool IsCompatible(VkFormat viewFormat, VkFormat imageFormat);
	VkImage                    _image;
	VkImageViewType            _type;
	VkFormat                   _format;
	VkComponentMapping         _componentsMap;
	VkImageSubresourceRange    _range;
};


