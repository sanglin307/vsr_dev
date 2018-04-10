#pragma once

struct VkSwapchainKHR_T {

	VkResult Init(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo);

#ifdef VK_USE_PLATFORM_WIN32_KHR
	VkResult Init_Win32(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo);
	IDXGIFactory                    *_pFactory;
	IDXGIAdapter                    *_pAdapter;
	ID3D11Device                    *_pd3dDevice;
	ID3D11DeviceContext             *_pImmediateContext;
	D3D_FEATURE_LEVEL               _featureLevel;
#endif
};
