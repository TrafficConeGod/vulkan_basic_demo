#pragma once
#include "result.h"
#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
#include <cglm/struct/vec2.h>
#include <cglm/struct/vec3.h>

// Used on all render passes
typedef struct {
    vec3s position;
} general_pipeline_vertex_t;

typedef struct {
    vec3s normal;
    vec4s tangent;
    vec2s tex_coord;
} color_pipeline_vertex_t;

typedef union {
    void* data;
    general_pipeline_vertex_t* general_pipeline_vertices;
    color_pipeline_vertex_t* color_pipeline_vertices;
} vertex_array_t;

#define NUM_VERTEX_ARRAYS 2
#define GENERAL_PIPELINE_VERTEX_ARRAY_INDEX 0
#define COLOR_PIPELINE_VERTEX_ARRAY_INDEX 1

extern size_t num_vertex_bytes_array[NUM_VERTEX_ARRAYS];

typedef struct {
    size_t num_vertices;
    size_t num_indices;
    vertex_array_t vertex_arrays[NUM_VERTEX_ARRAYS];
    uint16_t* indices;
} mesh_t;

result_t load_gltf_mesh(const char* path, mesh_t* mesh);