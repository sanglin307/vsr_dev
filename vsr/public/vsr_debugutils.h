#pragma once

#include "vsr_define.h"
#include "vsr_instance.h"
#include "vsr_device.h"
#include "vsr_queue.h"
#include "vsr_commandbuffer.h"

VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT)

typedef VkFlags VkDebugUtilsMessengerCallbackDataFlagsEXT;
typedef VkFlags VkDebugUtilsMessengerCreateFlagsEXT;

typedef enum VkDebugUtilsMessageSeverityFlagBitsEXT {
	VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT = 0x00000001,
	VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT = 0x00000010,
	VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT = 0x00000100,
	VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT = 0x00001000,
	VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugUtilsMessageSeverityFlagBitsEXT;
typedef VkFlags VkDebugUtilsMessageSeverityFlagsEXT;

typedef enum VkDebugUtilsMessageTypeFlagBitsEXT {
	VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT = 0x00000001,
	VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT = 0x00000002,
	VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT = 0x00000004,
	VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugUtilsMessageTypeFlagBitsEXT;
typedef VkFlags VkDebugUtilsMessageTypeFlagsEXT;

typedef struct VkDebugUtilsObjectNameInfoEXT {
	VkStructureType    sType;
	const void*        pNext;
	VkObjectType       objectType;
	uint64_t           objectHandle;
	const char*        pObjectName;
} VkDebugUtilsObjectNameInfoEXT;

typedef struct VkDebugUtilsObjectTagInfoEXT {
	VkStructureType    sType;
	const void*        pNext;
	VkObjectType       objectType;
	uint64_t           objectHandle;
	uint64_t           tagName;
	size_t             tagSize;
	const void*        pTag;
} VkDebugUtilsObjectTagInfoEXT;

typedef struct VkDebugUtilsLabelEXT {
	VkStructureType    sType;
	const void*        pNext;
	const char*        pLabelName;
	float              color[4];
} VkDebugUtilsLabelEXT;

typedef struct VkDebugUtilsMessengerCallbackDataEXT {
	VkStructureType                              sType;
	const void*                                  pNext;
	VkDebugUtilsMessengerCallbackDataFlagsEXT    flags;
	const char*                                  pMessageIdName;
	int32_t                                      messageIdNumber;
	const char*                                  pMessage;
	uint32_t                                     queueLabelCount;
	VkDebugUtilsLabelEXT*                        pQueueLabels;
	uint32_t                                     cmdBufLabelCount;
	VkDebugUtilsLabelEXT*                        pCmdBufLabels;
	uint32_t                                     objectCount;
	VkDebugUtilsObjectNameInfoEXT*               pObjects;
} VkDebugUtilsMessengerCallbackDataEXT;

typedef VkBool32(VKAPI_PTR *PFN_vkDebugUtilsMessengerCallbackEXT)(
	VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT                  messageType,
	const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
	void*                                            pUserData);

typedef struct VkDebugUtilsMessengerCreateInfoEXT {
	VkStructureType                         sType;
	const void*                             pNext;
	VkDebugUtilsMessengerCreateFlagsEXT     flags;
	VkDebugUtilsMessageSeverityFlagsEXT     messageSeverity;
	VkDebugUtilsMessageTypeFlagsEXT         messageType;
	PFN_vkDebugUtilsMessengerCallbackEXT    pfnUserCallback;
	void*                                   pUserData;
} VkDebugUtilsMessengerCreateInfoEXT;



typedef VkResult(VKAPI_PTR *PFN_vkSetDebugUtilsObjectNameEXT)(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo);
typedef VkResult(VKAPI_PTR *PFN_vkSetDebugUtilsObjectTagEXT)(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo);
typedef void (VKAPI_PTR *PFN_vkQueueBeginDebugUtilsLabelEXT)(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef void (VKAPI_PTR *PFN_vkQueueEndDebugUtilsLabelEXT)(VkQueue queue);
typedef void (VKAPI_PTR *PFN_vkQueueInsertDebugUtilsLabelEXT)(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef void (VKAPI_PTR *PFN_vkCmdBeginDebugUtilsLabelEXT)(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef void (VKAPI_PTR *PFN_vkCmdEndDebugUtilsLabelEXT)(VkCommandBuffer commandBuffer);
typedef void (VKAPI_PTR *PFN_vkCmdInsertDebugUtilsLabelEXT)(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo);
typedef VkResult(VKAPI_PTR *PFN_vkCreateDebugUtilsMessengerEXT)(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger);
typedef void (VKAPI_PTR *PFN_vkDestroyDebugUtilsMessengerEXT)(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR *PFN_vkSubmitDebugUtilsMessageEXT)(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(
	VkDevice                                    device,
	const VkDebugUtilsObjectNameInfoEXT*        pNameInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(
	VkDevice                                    device,
	const VkDebugUtilsObjectTagInfoEXT*         pTagInfo);

VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(
	VkQueue                                     queue,
	const VkDebugUtilsLabelEXT*                 pLabelInfo);

VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(
	VkQueue                                     queue);

VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(
	VkQueue                                     queue,
	const VkDebugUtilsLabelEXT*                 pLabelInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer,
	const VkDebugUtilsLabelEXT*                 pLabelInfo);

VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer);

VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer,
	const VkDebugUtilsLabelEXT*                 pLabelInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
	VkInstance                                  instance,
	const VkDebugUtilsMessengerCreateInfoEXT*   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDebugUtilsMessengerEXT*                   pMessenger);

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
	VkInstance                                  instance,
	VkDebugUtilsMessengerEXT                    messenger,
	const VkAllocationCallbacks*                pAllocator);

VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(
	VkInstance                                  instance,
	VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);
#endif
