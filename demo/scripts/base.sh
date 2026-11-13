#!/bin/sh
# Base scene with no A3 features: two spheres, a plane, one point light, no antialiasing
. "$(dirname "$0")/common.sh"

build base
render base 3 0
