#pragma once

struct VkFramebuffer_T : public vsrDeviceResource, public MemoryAlloc<VkFramebuffer_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkFramebuffer_T(const VkFramebufferCreateInfo*   pCreateInfo);

	VkRenderPass                _renderPass;
	std::vector<VkImageView>    _vecAttachments;
	uint32_t                    _width;
	uint32_t                    _height;
	uint32_t                    _layers;
};
