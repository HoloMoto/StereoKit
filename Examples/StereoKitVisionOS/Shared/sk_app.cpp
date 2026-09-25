/* SPDX-License-Identifier: MIT */
/* Portable StereoKit sample app — same pattern as SKTemplate_NetCore.
 * Existing StereoKit developers: put your app logic here (or link your
 * existing .cpp / object files) and rebuild with the visionOS target.
 */

#include "sk_app.h"

#include <stereokit.h>
#include <stereokit_ui.h>

using namespace sk;

static pose_t  cube_pose;
static model_t cube = nullptr;

///////////////////////////////////////////

bool sk_app_init(void *visionos_layer_renderer) {
	sk_visionos_set_layer_renderer(visionos_layer_renderer);

	sk_settings_t settings = {};
	settings.app_name                = "StereoKit VisionOS";
	settings.assets_folder           = "Assets";
	settings.mode                    = app_mode_xr;
	settings.blend_preference        = display_blend_any_transparent;
	settings.no_flatscreen_fallback  = true;
	settings.visionos_layer_renderer = visionos_layer_renderer;

	if (!sk_init(settings))
		return false;

	cube_pose = { { 0, 0, -0.5f }, quat_identity };
	cube = model_create_mesh(
		mesh_gen_rounded_cube(vec3_one * 0.1f, 0.02f, 4),
		material_find(default_id_material_ui));

	return true;
}

///////////////////////////////////////////

bool sk_app_step(void) {
	return sk_step([]() {
		ui_handle_begin("Cube", cube_pose, model_get_bounds(cube), false);
		ui_handle_end();
		render_add_model(cube, pose_matrix(cube_pose, vec3_one));
	});
}

///////////////////////////////////////////

void sk_app_shutdown(void) {
	if (cube) { model_release(cube); cube = nullptr; }
	sk_shutdown();
}
