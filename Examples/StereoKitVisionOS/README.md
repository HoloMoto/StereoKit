# StereoKit → visionOS (Vision Pro)

This example is the **retargeting shell**: keep writing normal StereoKit app code, then rebuild for Vision Pro with one script.

## Idea

| Piece | Role |
|-------|------|
| `Shared/sk_app.cpp` | Your StereoKit app (same style as Windows / Android / NetCore template) |
| `Host/` | visionOS ImmersiveSpace + CompositorServices only |
| `../../tools/Build-VisionOS.sh` | Builds `libStereoKitC` for visionOS and opens the Xcode host |

Existing StereoKit developers should **not** rewrite app logic for Apple APIs. Drop (or link) your StereoKit code into `Shared/`, run the script, press Run in Xcode.

## One-button build

From the repo root on a Mac with Xcode + visionOS SDK:

```bash
./tools/Build-VisionOS.sh          # Debug
./tools/Build-VisionOS.sh Release  # Release
```

Optional but recommended:

```bash
brew install cmake ninja xcodegen
```

## Bring your own StereoKit app

1. Replace the sample cube in `Shared/sk_app.cpp` with your existing StereoKit C/C++ loop  
   (or add your sources under `Shared/` and call them from `sk_app_init` / `sk_app_step`).
2. Keep using StereoKit APIs (`sk_init`, `sk_step`, `ui_*`, `render_*`, …).
3. Re-run `./tools/Build-VisionOS.sh`.

C# apps follow the same idea once .NET visionOS hosting is wired: app code stays StereoKit, only the build target / host shell changes.

## Status

- Platform + CompositorServices XR backend scaffolding: in progress on `feature/visionpro-openxr`
- Metal swapchain + ARKit input: still TODO (null GPU stubs link today)
- This folder already gives the **build-target switch** developer experience
