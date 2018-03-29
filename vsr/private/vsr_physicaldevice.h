#pragma once


struct VkPhysicalDevice_T {
	static struct VkPhysicalDevice_T* _instance;
	static VkPhysicalDevice_T* Get();

	VkPhysicalDeviceFeatures Features = {
					true,	//    robustBufferAccess;
					true,	//    fullDrawIndexUint32;
					true,	//    imageCubeArray;
					true,	//    independentBlend;
					true,	//    geometryShader;
					true,	//    tessellationShader;
					true,	//    sampleRateShading;
					true,	//    dualSrcBlend;
					true,	//    logicOp;
					true,	//    multiDrawIndirect;
					true,	//    drawIndirectFirstInstance;
					true,	//    depthClamp;
					true,	//    depthBiasClamp;
					true,	//    fillModeNonSolid;
					true,	//    depthBounds;
					true,	//    wideLines;
					true,	//    largePoints;
					true,	//    alphaToOne;
					true,	//    multiViewport;
					true,	//    samplerAnisotropy;
					true,	//    textureCompressionETC2;
					true,	//    textureCompressionASTC_LDR;
					true,	//    textureCompressionBC;
					true,	//    occlusionQueryPrecise;
					true,	//    pipelineStatisticsQuery;
					true,	//    vertexPipelineStoresAndAtomics;
					true,	//    fragmentStoresAndAtomics;
					true,	//    shaderTessellationAndGeometryPointSize;
					true,	//    shaderImageGatherExtended;
					true,	//    shaderStorageImageExtendedFormats;
					true,	//    shaderStorageImageMultisample;
					true,	//    shaderStorageImageReadWithoutFormat;
					true,	//    shaderStorageImageWriteWithoutFormat;
					true,	//    shaderUniformBufferArrayDynamicIndexing;
					true,	//    shaderSampledImageArrayDynamicIndexing;
					true,	//    shaderStorageBufferArrayDynamicIndexing;
					true,	//    shaderStorageImageArrayDynamicIndexing;
					true,	//    shaderClipDistance;
					true,	//    shaderCullDistance;
					true,	//    shaderFloat64;
					true,	//    shaderInt64;
					true,	//    shaderInt16;
					true,	//    shaderResourceResidency;
					true,	//    shaderResourceMinLod;
					true,	//    sparseBinding;
					true,	//    sparseResidencyBuffer;
					true,	//    sparseResidencyImage2D;
					true,	//    sparseResidencyImage3D;
					true,	//    sparseResidency2Samples;
					true,	//    sparseResidency4Samples;
					true,	//    sparseResidency8Samples;
					true,	//    sparseResidency16Samples;
					true,	//    sparseResidencyAliased;
					true,	//    variableMultisampleRate;
					true	//    inheritedQueries;
	};

	void GetPhysicalDeviceQueueFamilyProperties( uint32_t* pQueueFamilyPropertyCount,VkQueueFamilyProperties* pQueueFamilyProperties);
	void GetPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* pFeatures);
	void GetPhysicalDeviceFormatProperties(VkFormat format, VkFormatProperties* pFormatProperties);
	void GetPhysicalDeviceProperties(VkPhysicalDeviceProperties* pProperties);
	void GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties);
 
};