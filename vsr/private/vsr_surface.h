#pragma once

#ifdef VK_USE_PLATFORM_WIN32_KHR

class WINSurface_T {
public:
	WINSurface_T(HINSTANCE hinstance, HWND hwnd);

private:
	HINSTANCE                       _hinstance;
	HWND                            _hwnd;
};

#endif