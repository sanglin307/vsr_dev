#pragma once

struct VkSurfaceKHR_T {
	VkSurfaceKHR_T();
	std::vector<VkSurfaceFormatKHR> _format;
	VkSurfaceCapabilitiesKHR _capability = {
		2,                  //minImageCount;
	    8,                  //maxImageCount;
		{ 0xFFFFFFFF,0xFFFFFFFF},  //currentExtent;
		{ 1,1 },                    //minImageExtent;
		{ 0xFFFFFFFF,0xFFFFFFFF},  //maxImageExtent;
	    1,                         //maxImageArrayLayers;
		VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,    //supportedTransforms;
		VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,    //currentTransform;
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,        //supportedCompositeAlpha;
		VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT|
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,   //supportedUsageFlags;
	};
};

#ifdef VK_USE_PLATFORM_WIN32_KHR

class WINSurface_T : public VkSurfaceKHR_T {
public:
	WINSurface_T(HINSTANCE hinstance, HWND hwnd);

private:
	HINSTANCE                       _hinstance;
	HWND                            _hwnd;
};

#endif