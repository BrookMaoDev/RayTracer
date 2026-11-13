#!/bin/sh
# Base scene with a lattice alpha map on both spheres (light passes through the gaps too)
. "$(dirname "$0")/common.sh"

build alpha_mapping -DALPHA
render alpha_mapping 3 1
