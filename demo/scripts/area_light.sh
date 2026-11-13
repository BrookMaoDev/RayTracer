#!/bin/sh
# Base scene with the point light replaced by a 4x4 area light (soft shadows).
# Antialiasing stays on so each pixel averages 16 x 64 light samples and the penumbra is smooth.
. "$(dirname "$0")/common.sh"

build area_light -DALS
render area_light 3 1
