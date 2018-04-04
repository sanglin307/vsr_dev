#pragma once

struct VkSurfaceKHR_T {
	VkSurfaceKHR_T();
	std::vector<VkSurfaceFormatKHR> _format;
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