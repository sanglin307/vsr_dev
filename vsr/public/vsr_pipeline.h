#pragma once

#include "vsr_define.h"
#include "vsr_shadermodule.h"

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineCache)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineLayout)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipeline)

typedef struct VkPipelineShaderStageCreateInfo {
	VkStructureType                     sType;
	const void*                         pNext;
	VkPipelineShaderStageCreateFlags    flags;
	VkShaderStageFlagBits               stage;
	VkShaderModule                      module;
	const char*                         pName;
	const VkSpecializationInfo*         pSpecializationInfo;
} VkPipelineShaderStageCreateInfo;