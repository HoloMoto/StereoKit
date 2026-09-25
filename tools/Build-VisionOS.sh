#!/usr/bin/env bash
# Build StereoKitC for visionOS, then generate / open the ImmersiveSpace host.
# This is the "button" for retargeting existing StereoKit app code to Vision Pro:
#   1) Put your StereoKit logic in Examples/StereoKitVisionOS/Shared (or link it)
#   2) Run this script
#   3) Press Run in Xcode against Apple Vision Pro / simulator
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

export PATH="/opt/homebrew/bin:/usr/local/bin:${PATH}"

CONFIG="${1:-Debug}"
BUILD_DIR="bin/intermediate/visionOS_Arm64_${CONFIG}"
DIST_DIR="bin/distribute/bin/visionOS/arm64/${CONFIG}"
EXAMPLE_DIR="Examples/StereoKitVisionOS"

if [[ "$(uname -s)" != "Darwin" ]]; then
  echo "visionOS builds require macOS + Xcode with the visionOS SDK."
  exit 1
fi

if ! command -v cmake >/dev/null 2>&1; then
  echo "cmake not found. Install CMake (brew install cmake)."
  exit 1
fi

if ! xcrun --sdk xros --show-sdk-path >/dev/null 2>&1; then
  echo "visionOS SDK not found. Install it from Xcode → Settings → Platforms."
  exit 1
fi

SDK="$(xcrun --sdk xros --show-sdk-path)"
CC="$(xcrun --sdk xros --find clang)"
CXX="$(xcrun --sdk xros --find clang++)"

echo "==> [1/3] Building StereoKitC for visionOS (${CONFIG})"
cmake -S . -B "${BUILD_DIR}" -G Ninja \
  -DCMAKE_SYSTEM_NAME=visionOS \
  -DCMAKE_OSX_SYSROOT="${SDK}" \
  -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_C_COMPILER="${CC}" \
  -DCMAKE_CXX_COMPILER="${CXX}" \
  -DCMAKE_OBJCXX_COMPILER="${CXX}" \
  -DCMAKE_BUILD_TYPE="${CONFIG}" \
  -DSK_BUILD_OPENXR_LOADER=OFF \
  -DSK_BUILD_TESTS=OFF \
  -DSK_PHYSICS=OFF

cmake --build "${BUILD_DIR}" --target StereoKitC -j"$(sysctl -n hw.ncpu)"

mkdir -p "${DIST_DIR}"
cp -f "${BUILD_DIR}/libStereoKitC.dylib" "${DIST_DIR}/"
cp -f StereoKitC/stereokit.h StereoKitC/stereokit_ui.h bin/distribute/include/ 2>/dev/null || true

echo "==> [2/3] Preparing ImmersiveSpace host project"
cd "${EXAMPLE_DIR}"
if command -v xcodegen >/dev/null 2>&1; then
  xcodegen generate --spec project.yml
  echo "Generated StereoKitVisionOS.xcodeproj via XcodeGen"
else
  echo "XcodeGen not found (optional). Install with: brew install xcodegen"
  echo "Falling back to opening the folder — create an Xcode visionOS App and add Host/ + Shared/."
fi

echo "==> [3/3] Opening host"
if [[ -d StereoKitVisionOS.xcodeproj ]]; then
  open StereoKitVisionOS.xcodeproj
else
  open .
fi

cat <<EOF

Done.
  Native lib: ${DIST_DIR}/libStereoKitC.dylib
  App code:   ${EXAMPLE_DIR}/Shared/sk_app.cpp   ← put existing StereoKit logic here
  Host shell: ${EXAMPLE_DIR}/Host/              ← visionOS ImmersiveSpace only

In Xcode: select Apple Vision Pro (device or simulator) and press Run.
Metal drawable submission is still TODO — this wires the retargeting flow.
EOF
