/* SPDX-License-Identifier: MIT */
/* The authors below grant copyright rights under the MIT license:
 * Copyright (c) 2019-2023 Nick Klingensmith
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * Copyright (c) 2026 HoloMoto / StereoKit visionOS port
 */

#pragma once
#include "_platform.h"

#if defined(SK_OS_VISIONOS)

namespace sk {

///////////////////////////////////////////
// Host apps (SwiftUI ImmersiveSpace) create a CompositorServices
// LayerRenderer and pass it here before sk_init / during startup.
///////////////////////////////////////////

void visionos_set_layer_renderer(void *layer_renderer);
void *visionos_get_layer_renderer();

} // namespace sk
#endif // defined(SK_OS_VISIONOS)
