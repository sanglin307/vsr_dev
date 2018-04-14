#include "vsr_common.h"
#include "vsr_image.h"

VkAllocationCallbacks *MemoryAlloc<VkImage_T, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE>::_pAllocator = nullptr;
VkImage_T::VkImage_T(VkFormat format, VkColorSpaceKHR colorSpace, VkExtent2D extent, uint32_t arrayLayers, VkImageUsageFlags usage, VkSharingMode sharingMode)
:_format(format),_colorSpace(colorSpace),_extent(extent),_arrayLayers(arrayLayers),_usage(usage),_sharingMode(sharingMode)
{
}

VkImage_T::VkImage_T(const VkImageCreateInfo *pCreateInfo)
{

}

VkImage_T::~VkImage_T()
{

}

VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements(
	VkDevice                                    device,
	VkImage                                     image,
	VkMemoryRequirements*                       pMemoryRequirements)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateImage(
	VkDevice                                    device,
	const VkImageCreateInfo*                    pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkImage*                                    pImage)
{
	try
	{
		*pImage = new(pAllocator) VkImage_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyImage(
	VkDevice                                    device,
	VkImage                                     image,
	const VkAllocationCallbacks*                pAllocator)
{
	delete image;
}

VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout(
	VkDevice                                    device,
	VkImage                                     image,
	const VkImageSubresource*                   pSubresource,
	VkSubresourceLayout*                        pLayout)
{

}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateImageView(
	VkDevice                                    device,
	const VkImageViewCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkImageView*                                pView)
{
	
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyImageView(
	VkDevice                                    device,
	VkImageView                                 imageView,
	const VkAllocationCallbacks*                pAllocator)
{

}