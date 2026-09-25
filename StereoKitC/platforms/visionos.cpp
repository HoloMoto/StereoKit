/* SPDX-License-Identifier: MIT */
/* The authors below grant copyright rights under the MIT license:
 * Copyright (c) 2019-2023 Nick Klingensmith
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * Copyright (c) 2026 HoloMoto / StereoKit visionOS port
 */

#include "visionos.h"
#if defined(SK_OS_VISIONOS)

#include "../_stereokit.h"
#include "../log.h"
#include "../sk_memory.h"
#include "../libraries/array.h"
#include "platform.h"

#include <sk_gpu.h>
#include <unistd.h>
#include <time.h>

namespace sk {

struct platform_visionos_state_t {
	void *layer_renderer;
};
static platform_visionos_state_t local = {};

///////////////////////////////////////////

void visionos_set_layer_renderer(void *layer_renderer) {
	local.layer_renderer = layer_renderer;
}

///////////////////////////////////////////

void *visionos_get_layer_renderer() {
	return local.layer_renderer;
}

///////////////////////////////////////////

bool platform_impl_init() {
	const sk_settings_t *settings = sk_get_settings_ref();
	if (settings->visionos_layer_renderer != nullptr)
		local.layer_renderer = settings->visionos_layer_renderer;

	if (local.layer_renderer == nullptr) {
		log_warn("visionOS: no LayerRenderer provided yet. Call visionos_set_layer_renderer() or set sk_settings_t::visionos_layer_renderer from your ImmersiveSpace host before entering XR mode.");
	}
	return true;
}

///////////////////////////////////////////

void platform_impl_shutdown() {
	local = {};
}

///////////////////////////////////////////

void platform_impl_step() {
}

///////////////////////////////////////////

platform_win_type_ platform_win_type() { return platform_win_type_none; }

///////////////////////////////////////////

platform_win_t platform_win_make(const char *, recti_t, platform_surface_) { return -1; }

///////////////////////////////////////////

platform_win_t platform_win_get_existing(platform_surface_) { return -1; }

///////////////////////////////////////////

void platform_win_destroy(platform_win_t) {
}

///////////////////////////////////////////

bool platform_win_next_event(platform_win_t, platform_evt_ *out_event, platform_evt_data_t *) {
	*out_event = platform_evt_none;
	return false;
}

///////////////////////////////////////////

recti_t platform_win_rect(platform_win_t) {
	return { 0, 0, 0, 0 };
}

///////////////////////////////////////////

skg_swapchain_t *platform_win_get_swapchain(platform_win_t) {
	return nullptr;
}

///////////////////////////////////////////

bool platform_get_cursor(vec2 *out_pos) {
	*out_pos = { 0, 0 };
	return false;
}

///////////////////////////////////////////

void platform_set_cursor(vec2) {
}

///////////////////////////////////////////

float platform_get_scroll() {
	return 0;
}

///////////////////////////////////////////

void platform_xr_keyboard_show(bool) {
}

///////////////////////////////////////////

bool platform_xr_keyboard_present() {
	return false;
}

///////////////////////////////////////////

bool platform_xr_keyboard_visible() {
	return false;
}

///////////////////////////////////////////

bool platform_key_save_bytes(const char *, void *, int32_t) {
	return false;
}

///////////////////////////////////////////

bool platform_key_load_bytes(const char *, void *, int32_t) {
	return false;
}

///////////////////////////////////////////

font_t platform_default_font() {
	array_t<const char *> fonts  = {};
	font_t                result = nullptr;

	// visionOS shares many system font paths with iOS / macOS
	if      (platform_file_exists("/System/Library/Fonts/SFNS.ttf")) fonts.add("/System/Library/Fonts/SFNS.ttf");
	else if (platform_file_exists("/System/Library/Fonts/Core/SFNS.ttf")) fonts.add("/System/Library/Fonts/Core/SFNS.ttf");
	else if (platform_file_exists("/System/Library/Fonts/Helvetica.ttc")) fonts.add("/System/Library/Fonts/Helvetica.ttc");

	if (platform_file_exists("/System/Library/Fonts/ヒラギノ角ゴシック W3.ttc"))
		fonts.add("/System/Library/Fonts/ヒラギノ角ゴシック W3.ttc");
	else if (platform_file_exists("/System/Library/Fonts/Core/Hiragino Sans GB.ttc"))
		fonts.add("/System/Library/Fonts/Core/Hiragino Sans GB.ttc");

	if (fonts.count > 0)
		result = font_create_files(fonts.data, (int32_t)fonts.count);
	fonts.free();
	return result;
}

///////////////////////////////////////////

void platform_iterate_dir(const char *, void *, void (*)(void *, const char *, const platform_file_attr_t)) {
}

///////////////////////////////////////////

void platform_msgbox_err(const char *text, const char *header) {
	log_errf("%s: %s", header, text);
}

///////////////////////////////////////////

void platform_print_callstack() {
}

///////////////////////////////////////////

void platform_debug_output(log_, const char *) {
}

///////////////////////////////////////////

void platform_sleep(int ms) {
	struct timespec t = {
		(time_t)(ms / 1000),
		(long)((ms % 1000) * 1000000)
	};
	nanosleep(&t, nullptr);
}

} // namespace sk
#endif // defined(SK_OS_VISIONOS)
