#pragma once

struct VkImage_T : public MemoryAlloc<VkImage_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE> {
	VkImage_T(VkFormat format,VkColorSpaceKHR colorSpace,VkExtent2D extent, uint32_t arrayLayers,VkImageUsageFlags usage,VkSharingMode sharingMode);
	VkImage_T(const VkImageCreateInfo *pCreateInfo);
	~VkImage_T();

	VkFormat                         _format;
	VkColorSpaceKHR                  _colorSpace;
	VkExtent2D                       _extent;
	uint32_t                         _arrayLayers;
	VkImageUsageFlags                _usage;
	VkSharingMode                    _sharingMode;

	uint8_t*                         _pByteData;
};