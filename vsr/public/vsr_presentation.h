#pragma once

typedef struct VkSubmitInfo {
	VkStructureType                sType;
	const void*                    pNext;
	uint32_t                       waitSemaphoreCount;
	const VkSemaphore*             pWaitSemaphores;
	const VkPipelineStageFlags*    pWaitDstStageMask;
	uint32_t                       commandBufferCount;
	const VkCommandBuffer*         pCommandBuffers;
	uint32_t                       signalSemaphoreCount;
	const VkSemaphore*             pSignalSemaphores;
} VkSubmitInfo;