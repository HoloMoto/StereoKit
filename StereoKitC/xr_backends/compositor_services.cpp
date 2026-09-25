/* SPDX-License-Identifier: MIT */
/* The authors below grant copyright rights under the MIT license:
 * Copyright (c) 2026 HoloMoto / StereoKit visionOS port
 */

#include "compositor_services.h"
#if defined(SK_XR_COMPOSITOR)

#include "../_stereokit.h"
#include "../device.h"
#include "../log.h"
#include "../libraries/stref.h"
#include "../platforms/visionos.h"
#include "../sk_memory.h"
#include "../systems/render.h"

// CompositorServices / LayerRenderer are Objective-C types. Keep this file as
// pure C++ and treat the host-provided LayerRenderer as an opaque pointer for
// now. A follow-up .mm unit will call into cp_layer_renderer_* APIs.

namespace sk {

struct compositor_state_t {
	bool  running;
	void *layer_renderer;
};
static compositor_state_t local = {};

///////////////////////////////////////////

bool compositor_init() {
	local = {};
	local.layer_renderer = visionos_get_layer_renderer();

	device_data.display_type         = display_type_stereo;
	device_data.display_blend        = display_blend_any_transparent;
	device_data.display_refresh_rate = 90;
	device_data.tracking             = device_tracking_6dof;
	device_data.has_eye_gaze         = true;
	device_data.has_hand_tracking    = true;

	sk_free(device_data.name);
	sk_free(device_data.runtime);
	device_data.name    = string_copy("Apple Vision Pro");
	device_data.runtime = string_copy("CompositorServices");

	if (local.layer_renderer == nullptr) {
		log_warn("visionOS: LayerRenderer not set; XR session will still start so host glue can be iterated. Set sk_settings_t::visionos_layer_renderer from ImmersiveSpace.");
	} else {
		log_infof("visionOS: LayerRenderer acquired (%p). Metal swapchain + ARKit input still TODO.", local.layer_renderer);
	}

	// Metal drawable submission and ARKit world/hand/eye providers are next.
	// sk_gpu currently uses SKG_FORCE_NULL on this branch.
	local.running = true;
	return true;
}

///////////////////////////////////////////

void compositor_shutdown() {
	local = {};
}

///////////////////////////////////////////

void compositor_step_begin() {
	if (!local.running) return;
	// TODO: query next CompositorServices frame, bind Metal drawables,
	// update head pose from ARKit WorldTrackingProvider.
}

///////////////////////////////////////////

void compositor_step_end() {
	if (!local.running) return;
	// TODO: submit finished drawables / end frame to LayerRenderer.
}

} // namespace sk
#endif // defined(SK_XR_COMPOSITOR)
