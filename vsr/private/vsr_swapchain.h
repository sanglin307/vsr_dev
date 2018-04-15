#pragma once

struct VkSwapchainKHR_T : public MemoryAlloc<VkSwapchainKHR_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {

	VkResult init(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo);
	~VkSwapchainKHR_T();

	VkResult GetSwapchainImagesKHR(uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages);

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
