#!/bin/sh
# Base scene with texture maps: wood (right sphere), gold (left sphere), marble (floor)
. "$(dirname "$0")/common.sh"

build texture_mapping -DTEXTURES
render texture_mapping 3 1
