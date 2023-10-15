#include <vk_initializers.h>


VkCommandPoolCreateInfo vkinit::command_pool_create_info(uint32_t queuFamilyIndex, VkCommandPoolCreateFlags flags)
{
	// Create a command pool for commands submitted to the graphics queue
	VkCommandPoolCreateInfo commandPoolInfo = {};
	commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolInfo.pNext = nullptr;

	// The command pool will be one that can submit graphics commands
	commandPoolInfo.queueFamilyIndex = queuFamilyIndex;
	// also want the pool to allow for resetting of individual command buffers
	commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	return commandPoolInfo;
}

VkCommandBufferAllocateInfo vkinit::command_buffer_allocate_info(VkCommandPool pool, uint32_t count, VkCommandBufferLevel level)
{
	VkCommandBufferAllocateInfo cmdAllocInfo = {};
	cmdAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmdAllocInfo.pNext = nullptr;

	// commands will be made from the _commandPool
	cmdAllocInfo.commandPool = pool;
	// we will allocate 1 command buffer
	cmdAllocInfo.commandBufferCount = 1;
	// command level is primary
	cmdAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	return cmdAllocInfo;

}