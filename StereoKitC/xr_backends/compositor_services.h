/* SPDX-License-Identifier: MIT */
/* The authors below grant copyright rights under the MIT license:
 * Copyright (c) 2026 HoloMoto / StereoKit visionOS port
 */

#pragma once

#include "../platforms/platform.h"
#if defined(SK_XR_COMPOSITOR)

namespace sk {

///////////////////////////////////////////
// visionOS XR backend
//
// Apple Vision Pro does not ship a native OpenXR runtime. This backend maps
// StereoKit's XR lifecycle onto CompositorServices (LayerRenderer), with
// tracking/input intended to come from ARKit. OpenXR apps that need to reach
// Vision Pro today should use NVIDIA CloudXR / Foveated Streaming from a
// desktop OpenXR runtime instead.
///////////////////////////////////////////

bool compositor_init      ();
void compositor_shutdown  ();
void compositor_step_begin();
void compositor_step_end  ();

} // namespace sk
#endif // defined(SK_XR_COMPOSITOR)
