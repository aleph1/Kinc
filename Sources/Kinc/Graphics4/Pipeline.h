#pragma once

#include <Kinc/Graphics4/ConstantLocation.h>
#include <Kinc/Graphics4/TextureUnit.h>

#include <Kore/PipelineStateImpl.h>

#ifdef __cplusplus
extern "C" {
#endif

struct kinc_g4_vertex_structure;
struct kinc_g4_shader;

typedef enum {
	KINC_G4_BLEND_ONE,
	KINC_G4_BLEND_ZERO,
	KINC_G4_BLEND_SOURCE_ALPHA,
	KINC_G4_BLEND_DEST_ALPHA,
	KINC_G4_BLEND_INV_SOURCE_ALPHA,
	KINC_G4_BLEND_INV_DEST_ALPHA,
	KINC_G4_BLEND_SOURCE_COLOR,
	KINC_G4_BLEND_DEST_COLOR,
	KINC_G4_BLEND_INV_SOURCE_COLOR,
	KINC_G4_BLEND_INV_DEST_COLOR
} Kinc_G4_BlendingOperation;

typedef enum {
	KINC_G4_COMPARE_ALWAYS,
	KINC_G4_COMPARE_NEVER,
	KINC_G4_COMPARE_EQUAL,
	KINC_G4_COMPARE_NOT_EQUAL,
	KINC_G4_COMPARE_LESS,
	KINC_G4_COMPARE_LESS_EQUAL,
	KINC_G4_COMPARE_GREATER,
	KINC_G4_COMPARE_GREATER_EQUAL
} Kinc_G4_CompareMode;

typedef enum {
	KINC_G4_CULL_CLOCKWISE,
	KINC_G4_CULL_COUNTER_CLOCKWISE,
	KINC_G4_CULL_NOTHING
} Kinc_G4_CullMode;

typedef enum {
	KINC_G4_STENCIL_KEEP,
	KINC_G4_STENCIL_ZERO,
	KINC_G4_STENCIL_REPLACE,
	KINC_G4_STENCIL_INCREMENT,
	KINC_G4_STENCIL_INCREMENT_WRAP,
	KINC_G4_STENCIL_DECREMENT,
	KINC_G4_STENCIL_DECREMENT_WRAP,
	KINC_G4_STENCIL_INVERT
} Kinc_G4_StencilAction;

typedef struct kinc_g4_pipeline {
	struct kinc_g4_vertex_structure *input_layout[16];
	struct kinc_g4_shader *vertex_shader;
	struct kinc_g4_shader *fragment_shader;
	struct kinc_g4_shader *geometry_shader;
	struct kinc_g4_shader *tessellation_control_shader;
	struct kinc_g4_shader *tessellation_evaluation_shader;

	Kinc_G4_CullMode cull_mode;

	bool depth_write;
	Kinc_G4_CompareMode depth_mode;

	Kinc_G4_CompareMode stencil_mode;
	Kinc_G4_StencilAction stencil_both_pass;
	Kinc_G4_StencilAction stencil_depth_fail;
	Kinc_G4_StencilAction stencil_fail;
	int stencil_reference_value;
	int stencil_read_mask;
	int stencil_write_mask;

	// One, Zero deactivates blending
	Kinc_G4_BlendingOperation blend_source;
	Kinc_G4_BlendingOperation blend_destination;
	// BlendingOperation blendOperation;
	Kinc_G4_BlendingOperation alpha_blend_source;
	Kinc_G4_BlendingOperation alpha_blend_destination;
	// BlendingOperation alphaBlendOperation;

	bool color_write_mask_red[8]; // Per render target
	bool color_write_mask_green[8];
	bool color_write_mask_blue[8];
	bool color_write_mask_alpha[8];

	bool conservative_rasterization;

	Kinc_G4_PipelineStateImpl impl;
} kinc_g4_pipeline_t;

void kinc_g4_pipeline_init(kinc_g4_pipeline_t *state);
void kinc_g4_pipeline_destroy(kinc_g4_pipeline_t *state);
void kinc_g4_pipeline_compile(kinc_g4_pipeline_t *state);
kinc_g4_constant_location_t kinc_g4_pipeline_get_constant_location(kinc_g4_pipeline_t *state, const char *name);
kinc_g4_texture_unit_t kinc_g4_pipeline_get_texture_unit(kinc_g4_pipeline_t *state, const char *name);

void Kinc_G4_Internal_SetPipeline(kinc_g4_pipeline_t *pipeline);
void kinc_g4_internal_pipeline_set_defaults(kinc_g4_pipeline_t *pipeline);

#ifdef __cplusplus
}
#endif