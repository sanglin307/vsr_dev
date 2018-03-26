#pragma once

#include "vsr_define.h"

typedef enum VkQueryType {
	VK_QUERY_TYPE_OCCLUSION = 0,
	VK_QUERY_TYPE_PIPELINE_STATISTICS = 1,
	VK_QUERY_TYPE_TIMESTAMP = 2,
	VK_QUERY_TYPE_BEGIN_RANGE = VK_QUERY_TYPE_OCCLUSION,
	VK_QUERY_TYPE_END_RANGE = VK_QUERY_TYPE_TIMESTAMP,
	VK_QUERY_TYPE_RANGE_SIZE = (VK_QUERY_TYPE_TIMESTAMP - VK_QUERY_TYPE_OCCLUSION + 1),
	VK_QUERY_TYPE_MAX_ENUM = 0x7FFFFFFF
} VkQueryType;

typedef VkFlags VkQueueFlags;
typedef struct VkQueueFamilyProperties {
	VkQueueFlags    queueFlags;
	uint32_t        queueCount;
	uint32_t        timestampValidBits;
	VkExtent3D      minImageTransferGranularity;
} VkQueueFamilyProperties;

VK_DEFINE_HANDLE(VkQueue)
