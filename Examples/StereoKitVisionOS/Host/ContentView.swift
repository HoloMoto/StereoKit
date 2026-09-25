// SPDX-License-Identifier: MIT
import SwiftUI

struct ContentView: View {
	@Environment(\.openImmersiveSpace) private var openImmersiveSpace
	@Environment(\.dismissImmersiveSpace) private var dismissImmersiveSpace
	@State private var immersiveOpen = false

	var body: some View {
		VStack(spacing: 24) {
			Text("StereoKit × visionOS")
				.font(.largeTitle)
			Text("Same StereoKit app code as other platforms. This window is only the host shell — tap below to enter ImmersiveSpace.")
				.multilineTextAlignment(.center)
				.foregroundStyle(.secondary)
				.padding(.horizontal)

			Button(immersiveOpen ? "Exit StereoKit Immersive" : "Start StereoKit Immersive") {
				Task {
					if immersiveOpen {
						await dismissImmersiveSpace()
						immersiveOpen = false
					} else {
						await openImmersiveSpace(id: "StereoKitImmersive")
						immersiveOpen = true
					}
				}
			}
			.buttonStyle(.borderedProminent)
		}
		.padding(40)
	}
}
