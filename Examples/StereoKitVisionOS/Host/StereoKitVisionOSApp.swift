// SPDX-License-Identifier: MIT
// visionOS ImmersiveSpace host shell.
// Existing StereoKit app code lives in Shared/sk_app.cpp — this file only
// creates the Apple ImmersiveSpace and hands a LayerRenderer to StereoKit.

import SwiftUI
import CompositorServices

@main
struct StereoKitVisionOSApp: App {
	@State private var immersionStyle: ImmersionStyle = .mixed

	var body: some Scene {
		WindowGroup {
			ContentView()
		}

		ImmersiveSpace(id: "StereoKitImmersive") {
			CompositorLayer(configuration: StereoKitLayerConfiguration()) { layerRenderer in
				StereoKitSession.run(layerRenderer: layerRenderer)
			}
		}
		.immersionStyle(selection: $immersionStyle, in: .mixed, .full)
	}
}

struct StereoKitLayerConfiguration: CompositorLayerConfiguration {
	func makeConfiguration(capabilities: LayerRenderer.Capabilities,
	                       configuration: inout LayerRenderer.Configuration) {
		configuration.depthFormat = .depth32Float
		configuration.colorFormat = .bgra8Unorm_srgb
		let foveation = capabilities.supportsFoveation
		configuration.isFoveationEnabled = foveation
		let layouts = capabilities.supportedLayouts(options: foveation ? [.foveationEnabled] : [])
		configuration.layout = layouts.contains(.layered) ? .layered : .dedicated
	}
}
