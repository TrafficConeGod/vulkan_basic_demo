#pragma once
#include "vk.h"
#include "result.h"
#include <vk_mem_alloc.h>

// Graphics pipeline exclusive functions
result_t create_shader_module(const char* path, VkShaderModule* shader_module);
result_t create_buffer(VkDeviceSize num_buffer_bytes, VkBufferUsageFlags usage_flags, VmaAllocationCreateFlags allocation_flags, VkMemoryPropertyFlags property_flags, VkBuffer* buffer, VmaAllocation* buffer_allocation);
result_t create_mapped_buffer(VkDeviceSize num_buffer_bytes, VkBufferUsageFlags usage_flags, VmaAllocationCreateFlags allocation_flags, VkMemoryPropertyFlags property_flags, VkBuffer* buffer, VmaAllocation* buffer_allocation, void** mapped_data);
result_t write_to_staging_buffer(VmaAllocation staging_buffer_allocation, size_t num_bytes, const void* data);

void transfer_from_staging_buffer_to_buffer(VkCommandBuffer command_buffer, size_t num_bytes, VkBuffer staging_buffer, VkBuffer buffer);
void transfer_from_staging_buffer_to_image(VkCommandBuffer command_buffer, uint32_t image_width, uint32_t image_height, VkBuffer staging_buffer, VkImage image);
void transition_image_layout(VkCommandBuffer command_buffer, VkImage image, uint32_t num_mip_levels, uint32_t mip_level_index, VkImageLayout old_layout, VkImageLayout new_layout, VkAccessFlags src_access_flags, VkAccessFlags dest_access_flags, VkPipelineStageFlags src_stage_flags, VkPipelineStageFlags dest_stage_flags);

typedef struct {
    int width;
    int height;
} image_extent_t;

result_t begin_images(size_t num_images, const char* image_paths[], image_extent_t image_extents[], uint32_t num_mip_levels_array[], VkBuffer image_staging_buffers[], VmaAllocation image_staging_allocations[], VkImage images[], VmaAllocation image_allocations[]);
void transfer_images(
    VkCommandBuffer command_buffer,
    size_t num_images, const image_extent_t image_extents[], const uint32_t num_mip_levels_array[], const VkBuffer image_staging_buffers[], const VkImage images[]
);
void end_images(size_t num_images, const VkBuffer image_staging_buffers[], const VmaAllocation image_staging_buffer_allocations[]);
result_t create_image_views(size_t num_images, const uint32_t num_mip_levels_array[], const VkImage images[], VkImageView image_views[]);

typedef struct {
    VkDescriptorType type;
    VkShaderStageFlags stage_flags;
} descriptor_binding_t;

typedef struct {
    enum {
        descriptor_info_type_buffer,
        descriptor_info_type_image
    } type;
    union {
        VkDescriptorBufferInfo buffer;
        VkDescriptorImageInfo image;
    };
} descriptor_info_t;

typedef struct {
    uint32_t binding;
    VkFormat format;
    uint32_t offset;
} vertex_attribute_t;

typedef struct {
    VkShaderStageFlagBits stage_flags;
    VkShaderModule module;
} shader_t;

const char* create_graphics_pipeline(
    size_t num_shaders, const shader_t shaders[],
    size_t num_descriptor_bindings, const descriptor_binding_t descriptor_bindings[], const descriptor_info_t descriptor_infos[],
    size_t num_vertex_bindings, const uint32_t num_vertex_bytes_array[],
    size_t num_vertex_attributes, const vertex_attribute_t vertex_attributes[],
    size_t num_push_constants_bytes,
    VkRenderPass render_pass,
    VkDescriptorSetLayout* descriptor_set_layout, VkDescriptorPool* descriptor_pool, VkDescriptorSet* descriptor_set, VkPipelineLayout* pipeline_layout, VkPipeline* pipeline
);

// Used by core as well
result_t create_image(uint32_t image_width, uint32_t image_height, uint32_t num_mip_levels, VkFormat format, VkSampleCountFlagBits multisample_flags, VkImageTiling tiling, VkImageUsageFlags usage_flags, VkMemoryPropertyFlags property_flags, VkImage* image, VmaAllocation* image_allocation);
result_t create_image_view(VkImage image, uint32_t num_mip_levels, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView* image_view);
void destroy_images(size_t num_images, const VkImage images[], const VmaAllocation image_allocations[], const VkImageView image_views[]);