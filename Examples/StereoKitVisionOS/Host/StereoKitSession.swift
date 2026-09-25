// SPDX-License-Identifier: MIT
// Bridges CompositorServices LayerRenderer into the StereoKit C API and
// pumps sk_app_step on a dedicated render thread.

import Foundation
import CompositorServices
import Metal

enum StereoKitSession {
	private static var running = false

	static func run(layerRenderer: LayerRenderer) {
		guard !running else { return }
		running = true

		let rendererPointer = Unmanaged.passUnretained(layerRenderer).toOpaque()
		guard sk_app_init(rendererPointer) else {
			print("[StereoKit] sk_app_init failed — is libStereoKitC linked for visionOS?")
			running = false
			return
		}

		let thread = Thread {
			layerRenderer.waitUntilRunning()
			while layerRenderer.state != .invalidated && running {
				autoreleasepool {
					// Frame pacing will move into CompositorServices drawables
					// once Metal swapchain work lands. For now, keep StereoKit's
					// app loop alive so the host ↔ library glue can be tested.
					if !sk_app_step() {
						running = false
					}
					Thread.sleep(forTimeInterval: 1.0 / 90.0)
				}
			}
			sk_app_shutdown()
			running = false
		}
		thread.name = "StereoKit.Render"
		thread.qualityOfService = .userInteractive
		thread.start()
	}
}
