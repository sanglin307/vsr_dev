#pragma once

#include "vsr_define.h"

typedef VkFlags VkQueueFlags;
typedef struct VkQueueFamilyProperties {
	VkQueueFlags    queueFlags;
	uint32_t        queueCount;
	uint32_t        timestampValidBits;
	VkExtent3D      minImageTransferGranularity;
} VkQueueFamilyProperties;
