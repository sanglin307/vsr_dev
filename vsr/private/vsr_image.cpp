#include "vsr_common.h"
#include "vsr_image.h"
#include "vsr_device.h"
#include "vsr_physicaldevice.h"

VkAllocationCallbacks *MemoryAlloc<VkImage_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;

VkImage_T::VkImage_T(VkImageType type,VkFormat format, VkExtent3D extent, uint32_t mipLevels,uint32_t arrayLayers, VkImageTiling tiling,VkImageUsageFlags usage, VkSharingMode sharingMode,
	uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices, VkImageLayout layout)
:_type(type),_format(format),_extent(extent),_arrayLayers(arrayLayers), _mipLevels(mipLevels),_tiling(tiling),_usage(usage),_sharingMode(sharingMode),_layout(layout),_pData(nullptr)
{
	if (_sharingMode == VK_SHARING_MODE_CONCURRENT)
	{
		for (uint32_t i = 0; i < queueFamilyIndexCount; i++)
			_vecQueueFamilyIndices.push_back(pQueueFamilyIndices[i]);
	}

	if (_mipLevels > 1)
	{
		uint32_t maxLength = std::max(extent.width, extent.height);
		if (extent.depth > maxLength)
			maxLength = extent.depth;
		uint32_t mipMax = (uint32_t)std::floor(std::log2(maxLength)) + 1;
		if (mipMax < _mipLevels)
			_mipLevels = mipMax;
	}

	_totalsize = 0;
	_elementsize = 0;
	_planesize = 0;
	if (VkImage_T::IsDepthStencilFormat(format))
	{
		assert(type == VK_IMAGE_TYPE_2D);
		_elementsize = VkImage_T::GetDepthStencilFormatSize(format);
	}
	else
	{
		_elementsize = VkImage_T::GetImageComponentNum(format) * VkImage_T::GetImageComponentSize(format);
	}
	
	if (type == VK_IMAGE_TYPE_1D)
		_planesize = _elementsize * extent.width;
	else if (type == VK_IMAGE_TYPE_2D)
		_planesize = _elementsize * extent.width * extent.height;
	else if (type == VK_IMAGE_TYPE_3D)
		_planesize = _elementsize * extent.width * extent.height * extent.depth;

	if (_mipLevels > 1)
		_planesize = _planesize * 3 / 2;

	if (type != VK_IMAGE_TYPE_3D && _arrayLayers > 1)
		_totalsize = _planesize * _arrayLayers;
	else
		_totalsize = _planesize;
}

VkImage_T::VkImage_T(const VkImageCreateInfo *pCreateInfo)
{
	VkImage_T(pCreateInfo->imageType,pCreateInfo->format, pCreateInfo->extent,pCreateInfo->mipLevels,pCreateInfo->arrayLayers, pCreateInfo->tiling,pCreateInfo->usage, 
		pCreateInfo->sharingMode, pCreateInfo->queueFamilyIndexCount,pCreateInfo->pQueueFamilyIndices,pCreateInfo->initialLayout);
}

VkImage_T::~VkImage_T()
{
}

uint32_t VkImage_T::GetMipmapSize(uint32_t mipLevel)
{
	auto width = _extent.width;
	auto height = _extent.height;
	auto depth = _extent.depth;
	for (auto i = 0; i < mipLevel; i++)
	{
		if (width > 1)
			width /= 2;
		if (height > 1 && _type != VK_IMAGE_TYPE_1D)
			height /= 2;
		if (depth > 1 && _type == VK_IMAGE_TYPE_3D)
			depth /= 2;
	}
	
	if (_type == VK_IMAGE_TYPE_1D)
		return width * _elementsize;
	else if (_type == VK_IMAGE_TYPE_2D)
		return width * height * _elementsize;
	else if (_type == VK_IMAGE_TYPE_3D)
		return width * height * depth * _elementsize;

	return 0;

}

void VkImage_T::GetImageSubresourceLayout(VkDevice device, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout)
{
	*pLayout = { 0 };
	if (pSubresource->mipLevel >= _mipLevels || pSubresource->arrayLayer >= _arrayLayers)
		return;

	uint32_t mipOffset = 0;
	if (pSubresource->mipLevel > 0)
	{
		for (uint32_t i = 0; i < pSubresource->mipLevel; i++)
		{
			mipOffset += GetMipmapSize(i);
		}
	}
	pLayout->offset = pSubresource->arrayLayer * _planesize + mipOffset;
	pLayout->size = GetMipmapSize(pSubresource->mipLevel);
	pLayout->rowPitch = _extent.width;
	pLayout->arrayPitch = _planesize;
	if (_type == VK_IMAGE_TYPE_3D)
		pLayout->depthPitch = _planesize;
}

void VkImage_T::GetImageMemoryRequirements(VkDevice device,VkMemoryRequirements* pMemoryRequirements)
{
	pMemoryRequirements->alignment = Vk_Allocation_Alignment;
	pMemoryRequirements->size = _totalsize;
	VkPhysicalDeviceMemoryProperties prop;
	device->_physicalDevice->GetPhysicalDeviceMemoryProperties(&prop);
	if (_layout == VK_IMAGE_LAYOUT_PREINITIALIZED)
	{
		for (uint32_t i = 0; i < prop.memoryTypeCount; i++)
		{
			if (prop.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
			{
				pMemoryRequirements->memoryTypeBits = 1 << i;
				return;
			}
		}
	}
	else
	{
		for (uint32_t i = 0; i < prop.memoryTypeCount; i++)
		{
			if (prop.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
			{
				pMemoryRequirements->memoryTypeBits = 1 << i;
				return;
			}
		}
	}
	
	assert(0); // not find right memory type
	return;
}

uint32_t VkImage_T::GetImageComponentSize(VkFormat format)
{
	assert(!VkImage_T::IsDepthStencilFormat(format));
	if (format >= VK_FORMAT_R8_UNORM && format <= VK_FORMAT_B8G8R8A8_SRGB)
		return 1;
	else if (format >= VK_FORMAT_R16_UNORM && format <= VK_FORMAT_R16G16B16A16_SFLOAT)
		return 2;
	else if (format >= VK_FORMAT_R32_UINT && format <= VK_FORMAT_R32G32B32A32_SFLOAT)
		return 4;
	else if (format >= VK_FORMAT_R64_UINT && format <= VK_FORMAT_R64G64B64A64_SFLOAT)
		return 8;
	else
		assert(0);

	return 0;
}
uint32_t VkImage_T::GetImageComponentNum(VkFormat format)
{
	if (format >= VK_FORMAT_R8_UNORM && format <= VK_FORMAT_R8_SRGB ||
		format >= VK_FORMAT_R16_UNORM && format <= VK_FORMAT_R16_SFLOAT ||
		format >= VK_FORMAT_R32_UINT && format <= VK_FORMAT_R32_SFLOAT ||
		format >= VK_FORMAT_R64_UINT && format <= VK_FORMAT_R64_SFLOAT)
	{
		return 1;
	}
	else if (format >= VK_FORMAT_R8G8_UNORM && format <= VK_FORMAT_R8G8_SRGB ||
		format >= VK_FORMAT_R16G16_UNORM && format <= VK_FORMAT_R16G16_SFLOAT ||
		format >= VK_FORMAT_R32G32_UINT && format <= VK_FORMAT_R32G32_SFLOAT ||
		format >= VK_FORMAT_R64G64_UINT && format <= VK_FORMAT_R64G64_SFLOAT)
	{
		return 2;
	}
	else if (format >= VK_FORMAT_R8G8B8_UNORM && format <= VK_FORMAT_B8G8R8_SRGB ||
		format >= VK_FORMAT_R16G16B16_UNORM && format <= VK_FORMAT_R16G16B16_SFLOAT ||
		format >= VK_FORMAT_R32G32B32_UINT && format <= VK_FORMAT_R32G32B32_SFLOAT ||
		format >= VK_FORMAT_R64G64B64_UINT && format <= VK_FORMAT_R64G64B64_SFLOAT)
	{
		return 3;
	}
	else if (format >= VK_FORMAT_R8G8B8A8_UNORM && format <= VK_FORMAT_B8G8R8A8_SRGB ||
		format >= VK_FORMAT_R16G16B16A16_UNORM && format <= VK_FORMAT_R16G16B16A16_SFLOAT ||
		format >= VK_FORMAT_R32G32B32A32_UINT && format <= VK_FORMAT_R32G32B32A32_SFLOAT ||
		format >= VK_FORMAT_R64G64B64A64_UINT && format <= VK_FORMAT_R64G64B64A64_SFLOAT)
	{
		return 4;
	}
	else
		assert(0);

	return 0;
}

bool VkImage_T::IsDepthStencilFormat(VkFormat format)
{
	if (format >= VK_FORMAT_D16_UNORM && format <= VK_FORMAT_D32_SFLOAT_S8_UINT)
		return true;

	return false;
}

uint32_t VkImage_T::GetDepthStencilFormatSize(VkFormat format)
{
	switch(format)
	{
	case VK_FORMAT_S8_UINT:
		return 1;
	case VK_FORMAT_D16_UNORM :
		return 2;
	case VK_FORMAT_D16_UNORM_S8_UINT:
		return 3;
	case VK_FORMAT_X8_D24_UNORM_PACK32 :
	case VK_FORMAT_D32_SFLOAT:
	case VK_FORMAT_D24_UNORM_S8_UINT:
		return 4;
	case VK_FORMAT_D32_SFLOAT_S8_UINT:
		return 5;
	default:
		assert(0);
	}

	return 0;
}


VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements(
	VkDevice                                    device,
	VkImage                                     image,
	VkMemoryRequirements*                       pMemoryRequirements)
{
	image->GetImageMemoryRequirements(device,pMemoryRequirements);
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
	image->GetImageSubresourceLayout(device, pSubresource, pLayout);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

VkAllocationCallbacks *MemoryAlloc<VkImageView_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>::_pAllocator = nullptr;
VkImageView_T::VkImageView_T(const VkImageViewCreateInfo* pCreateInfo)
	:_image(pCreateInfo->image),_type(pCreateInfo->viewType),_format(pCreateInfo->format),_componentsMap(pCreateInfo->components),_range(pCreateInfo->subresourceRange)
{
	assert(IsCompatible(_format, _image->_format));
}

bool VkImageView_T::IsCompatible(VkFormat viewFormat, VkFormat imageFormat)
{
	if (VkImage_T::IsDepthStencilFormat(viewFormat))
		return viewFormat == imageFormat;

	return VkImage_T::GetImageComponentSize(viewFormat) == VkImage_T::GetImageComponentSize(imageFormat) &&
		VkImage_T::GetImageComponentNum(viewFormat) == VkImage_T::GetImageComponentNum(imageFormat);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateImageView(
	VkDevice                                    device,
	const VkImageViewCreateInfo*                pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkImageView*                                pView)
{
	try
	{
		*pView = new(pAllocator) VkImageView_T(pCreateInfo);
	}
	catch (...)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyImageView(
	VkDevice                                    device,
	VkImageView                                 imageView,
	const VkAllocationCallbacks*                pAllocator)
{
	delete imageView;
}