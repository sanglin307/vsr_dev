#pragma once

struct VkSwapchainKHR_T {

	VkResult Init(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo);
	void Exit();

	std::vector<VkImage_T*>         _vecImages;
#ifdef VK_USE_PLATFORM_WIN32_KHR
	VkResult Init_Win32(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo);
	void Exit_Win32();
	IDXGIFactory                    *_pFactory;
	IDXGIAdapter                    *_pAdapter;
	ID3D11Device                    *_pd3dDevice;
	ID3D11DeviceContext             *_pImmediateContext;
	IDXGISwapChain                  *_pSwapChain;
	ID3D11Texture2D                 *_pBackBuffer;
	D3D_FEATURE_LEVEL               _featureLevel;
#endif
};
