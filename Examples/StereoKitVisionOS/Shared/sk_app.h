/* SPDX-License-Identifier: MIT */
/* Shared StereoKit app entry used by the visionOS host.
 * This is intentionally the same style of code you would write for
 * Windows / Android / Linux — only the host shell changes per platform.
 */

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Call once from the ImmersiveSpace host after you have a LayerRenderer. */
bool sk_app_init(void *visionos_layer_renderer);

/* Drive one StereoKit frame. Call from the CompositorServices render loop. */
bool sk_app_step(void);

/* Tear down StereoKit when the immersive session ends. */
void sk_app_shutdown(void);

#ifdef __cplusplus
}
#endif
