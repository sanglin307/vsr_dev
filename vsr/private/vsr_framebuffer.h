#pragma once

struct VkFramebuffer_T : public MemoryAlloc<VkFramebuffer_T, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT> {
	VkFramebuffer_T(const VkFramebufferCreateInfo*   pCreateInfo);
};
