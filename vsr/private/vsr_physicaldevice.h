#pragma once


struct VkPhysicalDevice_T {
	static struct VkPhysicalDevice_T* _instance;
	static VkPhysicalDevice_T* Get();
};