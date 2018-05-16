#pragma once

struct VkImage_T : public vsrDeviceResource, public MemoryAlloc<VkImage_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkImage_T(VkImageType type,VkFormat format,VkExtent3D extent,uint32_t mipLevels,uint32_t arrayLayers,VkImageTiling tiling,VkImageUsageFlags usage,VkSharingMode sharingMode,
		      uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices, VkImageLayout layout);
	VkImage_T(const VkImageCreateInfo *pCreateInfo);
	~VkImage_T();

	void GetImageMemoryRequirements(VkDevice device, VkMemoryRequirements* pMemoryRequirements);
	void GetImageSubresourceLayout(VkDevice device, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout);
	inline void BindMemory(void* pData)
	{
		_pData = pData;
	}

	void* GetMemory(uint32_t layer, uint32_t mipLevel, VkOffset3D& offset);

	uint32_t GetMipmapSize(uint32_t mipLevel, VkExtent3D* extent);
	uint32_t GetMipmapOffset(uint32_t mipLevel);
	uint32_t GetTexelOffset(uint32_t mipLevel, VkOffset3D& offset);

	static uint32_t GetImageElementSize(VkFormat format);
	static uint32_t GetImageComponentSize(VkFormat format);
	static uint32_t GetImageComponentNum(VkFormat format);
	static bool IsDepthStencilFormat(VkFormat format);
	static uint32_t GetDepthStencilFormatSize(VkFormat format);

	VkImageType                      _type;
	VkFormat                         _format;
	VkExtent3D                       _extent;
	uint32_t                         _arrayLayers;
	uint32_t                         _mipLevels;
	VkImageUsageFlags                _usage;
	VkSharingMode                    _sharingMode;
	std::vector<uint32_t>            _vecQueueFamilyIndices;
	VkImageLayout                    _layout;
	VkImageTiling                    _tiling;

	uint32_t                         _elementsize;    // size for element for image , = component size * component num
	VkDeviceSize                     _layersize;      // size for one sub layer for image, including mipmap.
	VkDeviceSize                     _totalsize;
	void*                            _pData;
};

struct VkImageView_T : public vsrDeviceResource, public MemoryAlloc<VkImageView_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkImageView_T(const VkImageViewCreateInfo* pCreateInfo);

	static bool IsCompatible(VkFormat viewFormat, VkFormat imageFormat);
	VkImage                    _image;
	VkImageViewType            _type;
	VkFormat                   _format;
	VkComponentMapping         _componentsMap;
	VkImageSubresourceRange    _range;
};


