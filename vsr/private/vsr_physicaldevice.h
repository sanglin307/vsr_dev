#pragma once

#include "vsr_queue.h"


struct VkPhysicalDevice_T {
	static struct VkPhysicalDevice_T* _instance;
	static VkPhysicalDevice_T* Get();
 
	std::vector<vsrQueueFamily> _vecQueueFamily;
	VkPhysicalDeviceProperties Properties = {
		VK_API_VERSION_1_0,            //apiVersion;
		VK_MAKE_VERSION(0,1,0),        //driverVersion;
	    0,                             //vendorID;
	    0,                            //deviceID;
		VK_PHYSICAL_DEVICE_TYPE_CPU,  //deviceType;
	    "vsr",                        //deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];		  
		{0xbb, 0xf5, 0x03, 0x66, 0xb8, 0x4a, 0x47, 0x23, 0xa8, 0xbb, 0x6, 0x25, 0x11, 0x56, 0xa0, 0xe4},//pipelineCacheUUID[VK_UUID_SIZE];// {BBF50366-B84A-4723-A8BB-06251156A0E4}
		{   //limits
			16384,               // maxImageDimension1D;
			16384,               // maxImageDimension2D;
			2048,                // maxImageDimension3D;
			16384,               // maxImageDimensionCube;
			2048,                // maxImageArrayLayers;
			134217728,           // maxTexelBufferElements;
			65536,               //maxUniformBufferRange;
			4294967295,          //maxStorageBufferRange;
			256,                 //maxPushConstantsSize;
			4096,                //maxMemoryAllocationCount;
			4000,                 //maxSamplerAllocationCount;
			0x0000000000010000,   //bufferImageGranularity;
			0xffffffffffffffff,   //sparseAddressSpaceSize;
			8,                    //maxBoundDescriptorSets;
			4000,                 //maxPerStageDescriptorSamplers;
			12,                   //maxPerStageDescriptorUniformBuffers;
			4096,                 //maxPerStageDescriptorStorageBuffers;
			16384,                //maxPerStageDescriptorSampledImages;
			16384,                //maxPerStageDescriptorStorageImages;
			8,                    //maxPerStageDescriptorInputAttachments;
			53268,                //maxPerStageResources;
			4000,                 //maxDescriptorSetSamplers;
			72,                   //maxDescriptorSetUniformBuffers;
			72,                   //maxDescriptorSetUniformBuffersDynamic;
			4096,                 //maxDescriptorSetStorageBuffers;
			16,                   //maxDescriptorSetStorageBuffersDynamic;
			98304,                //maxDescriptorSetSampledImages;
			98304,                //maxDescriptorSetStorageImages;
			8,                    //maxDescriptorSetInputAttachments;
			32,                   //maxVertexInputAttributes;
			32,                   //maxVertexInputBindings;
			2047,                 //maxVertexInputAttributeOffset;
			2048,                 //maxVertexInputBindingStride;
			128,                  //maxVertexOutputComponents;
			64,                   //maxTessellationGenerationLevel;
			32,                   //maxTessellationPatchSize;
			128,                  //maxTessellationControlPerVertexInputComponents;
			128,                  //maxTessellationControlPerVertexOutputComponents;
			120,                  //maxTessellationControlPerPatchOutputComponents;
			4216,                 //maxTessellationControlTotalOutputComponents;
			128,                  //maxTessellationEvaluationInputComponents;
			128,                  //maxTessellationEvaluationOutputComponents;
			32,                   //maxGeometryShaderInvocations;
			128,                  //maxGeometryInputComponents;
			128,                   //maxGeometryOutputComponents;
			1024,                 //maxGeometryOutputVertices;
			1024,                 //maxGeometryTotalOutputComponents;
			128,                  //maxFragmentInputComponents;
			8,                    //maxFragmentOutputAttachments;
			1,                    //maxFragmentDualSrcAttachments;
			16,                   //maxFragmentCombinedOutputResources;
			49152,                //maxComputeSharedMemorySize;
			{2147483647, 65535, 65535},     //maxComputeWorkGroupCount[3];
			1536,                 //maxComputeWorkGroupInvocations;
			{ 1536, 1024, 64},    //maxComputeWorkGroupSize[3];
			8,                    //subPixelPrecisionBits;
			8,                    //subTexelPrecisionBits;
			8,                    //mipmapPrecisionBits;
			4294967295,           //maxDrawIndexedIndexValue;
	        4294967295,           //maxDrawIndirectCount;
			15,                   //maxSamplerLodBias;
			16,                   //maxSamplerAnisotropy;
			16,                   //maxViewports;
			{ 16384, 16384},      //maxViewportDimensions[2];
			{ -32768, 32768},     //viewportBoundsRange[2];
			8,                    //viewportSubPixelBits;
			0x0000000000000040,    //minMemoryMapAlignment;
			0x0000000000000010,    //minTexelBufferOffsetAlignment;
			0x0000000000000100,    //minUniformBufferOffsetAlignment;
			0x0000000000000020,    //minStorageBufferOffsetAlignment;
			-8,                    //minTexelOffset;
			7,                     //maxTexelOffset;
			-32,                   //minTexelGatherOffset;
			31,                    //maxTexelGatherOffset;
			-0.500000,             //minInterpolationOffset;
			0.437500,              //maxInterpolationOffset;
			4,                    //subPixelInterpolationOffsetBits;
			16384,                //maxFramebufferWidth;
	        16384,                //maxFramebufferHeight;
			2048,                 //maxFramebufferLayers;
			15,                   //framebufferColorSampleCounts;
			15,                   //framebufferDepthSampleCounts;
			15,                   //framebufferStencilSampleCounts;
			15,                   //framebufferNoAttachmentsSampleCounts;
			8,                    //maxColorAttachments;
			15,                   //sampledImageColorSampleCounts;
	        15,                   //sampledImageIntegerSampleCounts;
	        15,                   //sampledImageDepthSampleCounts;
	        15,                   //sampledImageStencilSampleCounts;
	        15,                   //storageImageSampleCounts;
			1,                    //maxSampleMaskWords;
			1,                    //timestampComputeAndGraphics;
			1,                    //timestampPeriod;
			8,                    //maxClipDistances;
			8,                    //maxCullDistances;
			8,                    //maxCombinedClipAndCullDistances;
			2,                    //discreteQueuePriorities;
			{ 1, 189.875000},     //pointSizeRange[2];
			{ 0.500000, 10},      //lineWidthRange[2];
		    0.125000,             //pointSizeGranularity;
			0.125000,             //lineWidthGranularity;
			1,                    //strictLines;
			1,                    //standardSampleLocations;
			0x0000000000000001,   //optimalBufferCopyOffsetAlignment;
			0x0000000000000001,   //optimalBufferCopyRowPitchAlignment;
			0x0000000000000040   //nonCoherentAtomSize;
	 },
	 {    //sparseProperties
		 1,                       //residencyStandard2DBlockShape;
		 1,                       //residencyStandard2DMultisampleBlockShape;
		 1,                       //residencyStandard3DBlockShape;
		 1,                       //residencyAlignedMipSize;
		 0                       //residencyNonResidentStrict;
	 }
	};

	VkPhysicalDeviceFeatures Features = {
					1,	//    robustBufferAccess;
					1,	//    fullDrawIndexUint32;
					1,	//    imageCubeArray;
					1,	//    independentBlend;
					1,	//    geometryShader;
					1,	//    tessellationShader;
					1,	//    sampleRateShading;
					1,	//    dualSrcBlend;
					1,	//    logicOp;
					1,	//    multiDrawIndirect;
					1,	//    drawIndirectFirstInstance;
					1,	//    depthClamp;
					1,	//    depthBiasClamp;
					1,	//    fillModeNonSolid;
					1,	//    depthBounds;
					1,	//    wideLines;
					1,	//    largePoints;
					1,	//    alphaToOne;
					1,	//    multiViewport;
					1,	//    samplerAnisotropy;
					0,	//    textureCompressionETC2;
					0,	//    textureCompressionASTC_LDR;
					1,	//    textureCompressionBC;
					1,	//    occlusionQueryPrecise;
					1,	//    pipelineStatisticsQuery;
					1,	//    vertexPipelineStoresAndAtomics;
					1,	//    fragmentStoresAndAtomics;
					1,	//    shaderTessellationAndGeometryPointSize;
					1,	//    shaderImageGatherExtended;
					1,	//    shaderStorageImageExtendedFormats;
					1,	//    shaderStorageImageMultisample;
					1,	//    shaderStorageImageReadWithoutFormat;
					1,	//    shaderStorageImageWriteWithoutFormat;
					1,	//    shaderUniformBufferArrayDynamicIndexing;
					1,	//    shaderSampledImageArrayDynamicIndexing;
					1,	//    shaderStorageBufferArrayDynamicIndexing;
					1,	//    shaderStorageImageArrayDynamicIndexing;
					1,	//    shaderClipDistance;
					1,	//    shaderCullDistance;
					1,	//    shaderFloat64;
					1,	//    shaderInt64;
					1,	//    shaderInt16;
					0,	//    shaderResourceResidency;
					0,	//    shaderResourceMinLod;
					1,	//    sparseBinding;
					0,	//    sparseResidencyBuffer;
					0,	//    sparseResidencyImage2D;
					0,	//    sparseResidencyImage3D;
					0,	//    sparseResidency2Samples;
					0,	//    sparseResidency4Samples;
					0,	//    sparseResidency8Samples;
					0,	//    sparseResidency16Samples;
					0,	//    sparseResidencyAliased;
					1,	//    variableMultisampleRate;
					1	//    inheritedQueries;
	};

	VkFormatProperties FormatProperties[VK_FORMAT_BC7_SRGB_BLOCK+1] =
	{
	   {
			0,
			0,
			0
	    }, {
			54273,
			54273,
			8
		}, {
			54273,
			54273,
			8
		}, {
			54273,
			54273,
			8
		}, {
			54273,
			56705,
			8
		}, {
			54273,
			54273,
			8
		}, {
			54273,
			54273,
			8
		}, {
			54273,
			54273,
			8
		}, {
			54273,
			56705,
			8
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			0,
			0,
			0
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			0
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			0
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56705,
			0
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			54273,
			72
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			50177,
			72
		}, {
			50177,
			50177,
			72
		}, {
			54273,
			56705,
			0
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56705,
			0
		}, {
			54273,
			56705,
			72
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			50177,
			72
		}, {
			0,
			0,
			64
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			0,
			0,
			64
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56707,
			88
		}, {
			50177,
			52359,
			120
		}, {
			50177,
			52359,
			120
		}, {
			54273,
			56711,
			120
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56707,
			88
		}, {
			50177,
			0,
			72
		}, {
			50177,
			0,
			72
		}, {
			54273,
			0,
			72
		}, {
			50177,
			52355,
			88
		}, {
			50177,
			52355,
			88
		}, {
			54273,
			56707,
			88
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			0,
			0,
			64
		}, {
			54273,
			56707,
			88
		}, {
			54273,
			54273,
			8
		}, {
			54273,
			54785,
			0
		}, {
			54273,
			54785,
			0
		}, {
			54273,
			54785,
			0
		}, {
			0,
			0,
			0
		}, {
			0,
			0,
			0
		}, {
			54273,
			54785,
			0
		}, {
			54273,
			54785,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}, {
			54273,
			54273,
			0
		}  // VK_FORMAT_BC7_SRGB_BLOCK
	};  

	void GetPhysicalDeviceQueueFamilyProperties( uint32_t* pQueueFamilyPropertyCount,VkQueueFamilyProperties* pQueueFamilyProperties);
	void GetPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* pFeatures);
	void GetPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties* pFormatProperties);
	void GetPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties);
	void GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties);

	VkResult GetPhysicalDeviceSurfaceSupportKHR(uint32_t queueFamilyIndex, VkSurfaceKHR  surface, VkBool32* pSupported);
	
	private:
		VkPhysicalDevice_T();
};