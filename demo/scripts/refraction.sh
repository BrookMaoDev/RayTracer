#!/bin/sh
# Separate refraction scene: a glass marble inside a larger glass sphere (2 nested refractive objects).
# Needs a deeper recursion depth than the other scenes.
. "$(dirname "$0")/common.sh"

build refraction -DSCENE_REFRACTION
render refraction 8 1
