/* SPDX-License-Identifier: MIT */
/* Temporary null GPU implementations for visionOS until Metal lands in sk_gpu.
 * Built only when SKG_FORCE_NULL is set. Complements the incomplete SKG_NULL
 * stubs inside sk_gpu.h so StereoKitC can link while CompositorServices work
 * continues.
 */

#include "../platforms/platform.h"
#if defined(SK_OS_VISIONOS)

#include <sk_gpu.h>
#include <string.h>

static skg_tex_t *skg_null_bound_target = nullptr;

int32_t skg_init(const char *, void *) { return 1; }
void    skg_shutdown() {}
const char *skg_adapter_name() { return "visionOS-null"; }
skg_platform_data_t skg_get_platform_data() { return {}; }
bool skg_capability(skg_cap_) { return false; }

void skg_event_begin(const char *) {}
void skg_event_end() {}
void skg_draw_begin() {}
void skg_draw(int32_t, int32_t, int32_t, int32_t) {}
void skg_compute(uint32_t, uint32_t, uint32_t) {}
void skg_viewport(const int32_t *) {}
void skg_viewport_get(int32_t *out_xywh) { if (out_xywh) memset(out_xywh, 0, sizeof(int32_t) * 4); }
void skg_scissor(const int32_t *) {}
void skg_target_clear(bool, const float *) {}

skg_buffer_t skg_buffer_create(const void *, uint32_t, uint32_t size_stride, skg_buffer_type_ type, skg_use_ use) {
	skg_buffer_t b = {};
	b.use = use; b.type = type; b.stride = size_stride;
	return b;
}
void skg_buffer_name(skg_buffer_t *, const char *) {}
bool skg_buffer_is_valid(const skg_buffer_t *) { return true; }
void skg_buffer_set_contents(skg_buffer_t *, const void *, uint32_t) {}
void skg_buffer_get_contents(const skg_buffer_t *, void *, uint32_t) {}
void skg_buffer_bind(const skg_buffer_t *, skg_bind_t) {}
void skg_buffer_clear(skg_bind_t) {}
void skg_buffer_destroy(skg_buffer_t *) {}

skg_mesh_t skg_mesh_create(const skg_buffer_t *, const skg_buffer_t *) { return {}; }
void skg_mesh_name(skg_mesh_t *, const char *) {}
void skg_mesh_set_verts(skg_mesh_t *, const skg_buffer_t *) {}
void skg_mesh_set_inds(skg_mesh_t *, const skg_buffer_t *) {}
void skg_mesh_bind(const skg_mesh_t *) {}
void skg_mesh_destroy(skg_mesh_t *) {}

void skg_shader_name(skg_shader_t *, const char *) {}
bool skg_shader_is_valid(const skg_shader_t *shader) { return shader != nullptr; }
void skg_shader_compute_bind(const skg_shader_t *) {}
void skg_shader_destroy(skg_shader_t *shader) { if (shader) *shader = {}; }

skg_pipeline_t skg_pipeline_create(skg_shader_t *shader) {
	skg_pipeline_t p = {};
	if (shader) p.meta = shader->meta;
	return p;
}
void skg_pipeline_name(skg_pipeline_t *, const char *) {}
void skg_pipeline_bind(const skg_pipeline_t *) {}
void skg_pipeline_set_transparency(skg_pipeline_t *p, skg_transparency_ t) { if (p) p->transparency = t; }
skg_transparency_ skg_pipeline_get_transparency(const skg_pipeline_t *p) { return p ? p->transparency : (skg_transparency_)0; }
void skg_pipeline_set_cull(skg_pipeline_t *p, skg_cull_ c) { if (p) p->cull = c; }
skg_cull_ skg_pipeline_get_cull(const skg_pipeline_t *p) { return p ? p->cull : (skg_cull_)0; }
void skg_pipeline_set_wireframe(skg_pipeline_t *p, bool w) { if (p) p->wireframe = w; }
bool skg_pipeline_get_wireframe(const skg_pipeline_t *p) { return p ? p->wireframe : false; }
void skg_pipeline_set_depth_write(skg_pipeline_t *p, bool w) { if (p) p->depth_write = w; }
bool skg_pipeline_get_depth_write(const skg_pipeline_t *p) { return p ? p->depth_write : false; }
void skg_pipeline_set_depth_test(skg_pipeline_t *p, skg_depth_test_ t) { if (p) p->depth_test = t; }
skg_depth_test_ skg_pipeline_get_depth_test(const skg_pipeline_t *p) { return p ? p->depth_test : (skg_depth_test_)0; }
void skg_pipeline_set_scissor(skg_pipeline_t *p, bool e) { if (p) p->scissor = e; }
bool skg_pipeline_get_scissor(const skg_pipeline_t *p) { return p ? p->scissor : false; }
void skg_pipeline_destroy(skg_pipeline_t *p) { if (p) *p = {}; }

skg_swapchain_t skg_swapchain_create(void *, skg_tex_fmt_, skg_tex_fmt_, int32_t w, int32_t h) {
	skg_swapchain_t s = {}; s.width = w; s.height = h; return s;
}
void skg_swapchain_resize(skg_swapchain_t *s, int32_t w, int32_t h) { if (s) { s->width = w; s->height = h; } }
void skg_swapchain_present(skg_swapchain_t *) {}
void skg_swapchain_bind(skg_swapchain_t *) {}
void skg_swapchain_destroy(skg_swapchain_t *) {}

skg_tex_t skg_tex_create_from_existing(void *, skg_tex_type_ type, skg_tex_fmt_ format, int32_t width, int32_t height, int32_t array_count, int32_t multisample, int32_t) {
	skg_tex_t t = {};
	t.type = type; t.format = format; t.width = width; t.height = height;
	t.array_count = array_count; t.multisample = multisample;
	return t;
}
skg_tex_t skg_tex_create_from_layer(void *, skg_tex_type_ type, skg_tex_fmt_ format, int32_t width, int32_t height, int32_t array_layer) {
	skg_tex_t t = {};
	t.type = type; t.format = format; t.width = width; t.height = height;
	t.array_start = array_layer; t.array_count = 1;
	return t;
}
skg_tex_t skg_tex_create(skg_tex_type_ type, skg_use_ use, skg_tex_fmt_ format, skg_mip_ mip_maps) {
	skg_tex_t t = {};
	t.type = type; t.use = use; t.format = format; t.mips = mip_maps;
	return t;
}
void skg_tex_name(skg_tex_t *, const char *) {}
bool skg_tex_is_valid(const skg_tex_t *tex) { return tex != nullptr; }
void skg_tex_copy_to(const skg_tex_t *, int32_t, skg_tex_t *, int32_t) {}
void skg_tex_copy_to_swapchain(const skg_tex_t *, skg_swapchain_t *) {}
void skg_tex_attach_depth(skg_tex_t *, skg_tex_t *) {}
void skg_tex_settings(skg_tex_t *, skg_tex_address_, skg_tex_sample_, int32_t) {}
void skg_tex_set_contents(skg_tex_t *tex, const void *, int32_t width, int32_t height) {
	if (tex) { tex->width = width; tex->height = height; }
}
void skg_tex_set_contents_arr(skg_tex_t *tex, const void **, int32_t array_count, int32_t, int32_t width, int32_t height, int32_t multisample) {
	if (tex) { tex->width = width; tex->height = height; tex->array_count = array_count; tex->multisample = multisample; }
}
bool skg_tex_get_contents(skg_tex_t *, void *, size_t) { return false; }
bool skg_tex_get_mip_contents(skg_tex_t *, int32_t, void *, size_t) { return false; }
bool skg_tex_get_mip_contents_arr(skg_tex_t *, int32_t, int32_t, void *, size_t) { return false; }
bool skg_tex_gen_mips(skg_tex_t *) { return false; }
void *skg_tex_get_native(const skg_tex_t *) { return nullptr; }
void skg_tex_bind(const skg_tex_t *, skg_bind_t) {}
void skg_tex_clear(skg_bind_t) {}
void skg_tex_target_bind(skg_tex_t *render_target, int32_t, int32_t) { skg_null_bound_target = render_target; }
skg_tex_t *skg_tex_target_get() { return skg_null_bound_target; }
void skg_tex_destroy(skg_tex_t *tex) { if (tex) *tex = {}; }
int64_t skg_tex_fmt_to_native(skg_tex_fmt_ format) { return (int64_t)format; }
skg_tex_fmt_ skg_tex_fmt_from_native(int64_t format) { return (skg_tex_fmt_)format; }
bool skg_tex_fmt_supported(skg_tex_fmt_) { return true; }

void skg_setup_xlib(void *, void *, void *, void *) {}

#endif // defined(SK_OS_VISIONOS)
