#include "vsr_common.h"

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
	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyImage(
	VkDevice                                    device,
	VkImage                                     image,
	const VkAllocationCallbacks*                pAllocator)
{

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