#pragma once

#include "vsr_define.h"

VK_DEFINE_HANDLE(VkDevice)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeviceMemory)

typedef PFN_vkVoidFunction(VKAPI_PTR *PFN_vkGetDeviceProcAddr)(VkDevice device, const char* pName);