// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>

//bootstrap library
#include "VkBootstrap.h"

#include <deque>
#include <functional>

class PipelineBuilder {
public:
	std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;
	VkPipelineVertexInputStateCreateInfo _vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
	VkViewport _viewport;
	VkRect2D _scissor;
	VkPipelineRasterizationStateCreateInfo _rasterizer;
	VkPipelineColorBlendAttachmentState _colorBlendAttachment;
	VkPipelineMultisampleStateCreateInfo _multisampling;
	VkPipelineLayout _pipelineLayout;

	VkPipeline build_pipeline(VkDevice device, VkRenderPass pass);
};

struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)(); //call the function
		}

		deletors.clear();
	}
};

class VulkanEngine {
public:

	VkInstance _instance; //Vulkan library handle
	VkDebugUtilsMessengerEXT _debug_messenger; // Vulkan debug output handle
	VkPhysicalDevice _chosenGPU; // GPU chosen as the default device
	VkDevice _device; // Vulkna device for commands
	VkSurfaceKHR _surface; // vulkan window surface

	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat; // Image format by the windowing system

	std::vector<VkImage> _swapchainImages;// Array of images from the swap chain
	std::vector<VkImageView> _swapchainImageViews; // Array of image views from the swapchain


	// Vulkan commands
	VkQueue _graphicsQueue; // Queue to submit to
	uint32_t _graphicsQueueFamily; // Family of that queue

	VkCommandPool _commandPool; // The comman pool for our commands
	VkCommandBuffer _mainCommandBuffer; // The buffer we will record into

	// Renderpass code
	VkRenderPass _renderPass;
	std::vector<VkFramebuffer> _frameBuffers;

	// Mainloop code
	VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;

	// Render pipeline
	VkPipelineLayout _trianglePipelineLayout;
	VkPipeline _trianglePipeline;
	VkPipeline _redTrianglePipeline;

	// Input keys
	int _selectedShader{ 0 };

	DeletionQueue _mainDeletionQueue;

	bool _isInitialized{ false };
	int _frameNumber {0};

	VkExtent2D _windowExtent{ 1700 , 900 };

	struct SDL_Window* _window{ nullptr };

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

private:
	// Initialize the vulkan framework
	void init_vulkan();

	// Initializing the swapchain
	void init_swapchain();

	// Initializing the commmand buffer and pool
	void init_commands();

	void init_default_renderpass();

	void init_framebuffers();

	void init_sync_structures();

	void init_pipelines();

	bool load_shader_module(const char* filePath, VkShaderModule* outShaderModule);
};
