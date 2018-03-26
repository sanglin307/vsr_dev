#pragma once

#include "vsr_define.h"
#include "vsr_queue.h"

VK_DEFINE_HANDLE(VkPhysicalDevice)

typedef enum VkPhysicalDeviceType {
	VK_PHYSICAL_DEVICE_TYPE_OTHER = 0,
	VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = 1,
	VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = 2,
	VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = 3,
	VK_PHYSICAL_DEVICE_TYPE_CPU = 4,
	VK_PHYSICAL_DEVICE_TYPE_BEGIN_RANGE = VK_PHYSICAL_DEVICE_TYPE_OTHER,
	VK_PHYSICAL_DEVICE_TYPE_END_RANGE = VK_PHYSICAL_DEVICE_TYPE_CPU,
	VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE = (VK_PHYSICAL_DEVICE_TYPE_CPU - VK_PHYSICAL_DEVICE_TYPE_OTHER + 1),
	VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM = 0x7FFFFFFF
} VkPhysicalDeviceType;

typedef struct VkPhysicalDeviceLimits {
	uint32_t              maxImageDimension1D;
	uint32_t              maxImageDimension2D;
	uint32_t              maxImageDimension3D;
	uint32_t              maxImageDimensionCube;
	uint32_t              maxImageArrayLayers;
	uint32_t              maxTexelBufferElements;
	uint32_t              maxUniformBufferRange;
	uint32_t              maxStorageBufferRange;
	uint32_t              maxPushConstantsSize;
	uint32_t              maxMemoryAllocationCount;
	uint32_t              maxSamplerAllocationCount;
	VkDeviceSize          bufferImageGranularity;
	VkDeviceSize          sparseAddressSpaceSize;
	uint32_t              maxBoundDescriptorSets;
	uint32_t              maxPerStageDescriptorSamplers;
	uint32_t              maxPerStageDescriptorUniformBuffers;
	uint32_t              maxPerStageDescriptorStorageBuffers;
	uint32_t              maxPerStageDescriptorSampledImages;
	uint32_t              maxPerStageDescriptorStorageImages;
	uint32_t              maxPerStageDescriptorInputAttachments;
	uint32_t              maxPerStageResources;
	uint32_t              maxDescriptorSetSamplers;
	uint32_t              maxDescriptorSetUniformBuffers;
	uint32_t              maxDescriptorSetUniformBuffersDynamic;
	uint32_t              maxDescriptorSetStorageBuffers;
	uint32_t              maxDescriptorSetStorageBuffersDynamic;
	uint32_t              maxDescriptorSetSampledImages;
	uint32_t              maxDescriptorSetStorageImages;
	uint32_t              maxDescriptorSetInputAttachments;
	uint32_t              maxVertexInputAttributes;
	uint32_t              maxVertexInputBindings;
	uint32_t              maxVertexInputAttributeOffset;
	uint32_t              maxVertexInputBindingStride;
	uint32_t              maxVertexOutputComponents;
	uint32_t              maxTessellationGenerationLevel;
	uint32_t              maxTessellationPatchSize;
	uint32_t              maxTessellationControlPerVertexInputComponents;
	uint32_t              maxTessellationControlPerVertexOutputComponents;
	uint32_t              maxTessellationControlPerPatchOutputComponents;
	uint32_t              maxTessellationControlTotalOutputComponents;
	uint32_t              maxTessellationEvaluationInputComponents;
	uint32_t              maxTessellationEvaluationOutputComponents;
	uint32_t              maxGeometryShaderInvocations;
	uint32_t              maxGeometryInputComponents;
	uint32_t              maxGeometryOutputComponents;
	uint32_t              maxGeometryOutputVertices;
	uint32_t              maxGeometryTotalOutputComponents;
	uint32_t              maxFragmentInputComponents;
	uint32_t              maxFragmentOutputAttachments;
	uint32_t              maxFragmentDualSrcAttachments;
	uint32_t              maxFragmentCombinedOutputResources;
	uint32_t              maxComputeSharedMemorySize;
	uint32_t              maxComputeWorkGroupCount[3];
	uint32_t              maxComputeWorkGroupInvocations;
	uint32_t              maxComputeWorkGroupSize[3];
	uint32_t              subPixelPrecisionBits;
	uint32_t              subTexelPrecisionBits;
	uint32_t              mipmapPrecisionBits;
	uint32_t              maxDrawIndexedIndexValue;
	uint32_t              maxDrawIndirectCount;
	float                 maxSamplerLodBias;
	float                 maxSamplerAnisotropy;
	uint32_t              maxViewports;
	uint32_t              maxViewportDimensions[2];
	float                 viewportBoundsRange[2];
	uint32_t              viewportSubPixelBits;
	size_t                minMemoryMapAlignment;
	VkDeviceSize          minTexelBufferOffsetAlignment;
	VkDeviceSize          minUniformBufferOffsetAlignment;
	VkDeviceSize          minStorageBufferOffsetAlignment;
	int32_t               minTexelOffset;
	uint32_t              maxTexelOffset;
	int32_t               minTexelGatherOffset;
	uint32_t              maxTexelGatherOffset;
	float                 minInterpolationOffset;
	float                 maxInterpolationOffset;
	uint32_t              subPixelInterpolationOffsetBits;
	uint32_t              maxFramebufferWidth;
	uint32_t              maxFramebufferHeight;
	uint32_t              maxFramebufferLayers;
	VkSampleCountFlags    framebufferColorSampleCounts;
	VkSampleCountFlags    framebufferDepthSampleCounts;
	VkSampleCountFlags    framebufferStencilSampleCounts;
	VkSampleCountFlags    framebufferNoAttachmentsSampleCounts;
	uint32_t              maxColorAttachments;
	VkSampleCountFlags    sampledImageColorSampleCounts;
	VkSampleCountFlags    sampledImageIntegerSampleCounts;
	VkSampleCountFlags    sampledImageDepthSampleCounts;
	VkSampleCountFlags    sampledImageStencilSampleCounts;
	VkSampleCountFlags    storageImageSampleCounts;
	uint32_t              maxSampleMaskWords;
	VkBool32              timestampComputeAndGraphics;
	float                 timestampPeriod;
	uint32_t              maxClipDistances;
	uint32_t              maxCullDistances;
	uint32_t              maxCombinedClipAndCullDistances;
	uint32_t              discreteQueuePriorities;
	float                 pointSizeRange[2];
	float                 lineWidthRange[2];
	float                 pointSizeGranularity;
	float                 lineWidthGranularity;
	VkBool32              strictLines;
	VkBool32              standardSampleLocations;
	VkDeviceSize          optimalBufferCopyOffsetAlignment;
	VkDeviceSize          optimalBufferCopyRowPitchAlignment;
	VkDeviceSize          nonCoherentAtomSize;
} VkPhysicalDeviceLimits;

typedef struct VkPhysicalDeviceSparseProperties {
	VkBool32    residencyStandard2DBlockShape;
	VkBool32    residencyStandard2DMultisampleBlockShape;
	VkBool32    residencyStandard3DBlockShape;
	VkBool32    residencyAlignedMipSize;
	VkBool32    residencyNonResidentStrict;
} VkPhysicalDeviceSparseProperties;

typedef struct VkPhysicalDeviceMemoryProperties {
	uint32_t        memoryTypeCount;
	VkMemoryType    memoryTypes[VK_MAX_MEMORY_TYPES];
	uint32_t        memoryHeapCount;
	VkMemoryHeap    memoryHeaps[VK_MAX_MEMORY_HEAPS];
} VkPhysicalDeviceMemoryProperties;

typedef struct VkPhysicalDeviceProperties {
	uint32_t                            apiVersion;
	uint32_t                            driverVersion;
	uint32_t                            vendorID;
	uint32_t                            deviceID;
	VkPhysicalDeviceType                deviceType;
	char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
	uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
	VkPhysicalDeviceLimits              limits;
	VkPhysicalDeviceSparseProperties    sparseProperties;
} VkPhysicalDeviceProperties;



VkResult vkEnumeratePhysicalDevices(
	VkInstance                                  instance,
	uint32_t*                                   pPhysicalDeviceCount,
	VkPhysicalDevice*                           pPhysicalDevices);

void vkGetPhysicalDeviceQueueFamilyProperties(
	VkPhysicalDevice                            physicalDevice,
	uint32_t*                                   pQueueFamilyPropertyCount,
	VkQueueFamilyProperties*                    pQueueFamilyProperties);