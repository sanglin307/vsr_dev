#pragma once

struct VkRenderPass_T : public vsrDeviceResource, public MemoryAlloc<VkRenderPass_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT>  {
	VkRenderPass_T(const VkRenderPassCreateInfo* pCreateInfo);
	std::vector<VkAttachmentDescription>   _vecAttachment;
	std::vector<VkSubpassDescription>      _vecSubpasses;
	std::vector<VkSubpassDependency>       _vecDependencies;
};