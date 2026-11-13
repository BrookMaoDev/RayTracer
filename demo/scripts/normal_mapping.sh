#!/bin/sh
# texture_mapping.sh plus the matching normal map on every object
. "$(dirname "$0")/common.sh"

build normal_mapping -DTEXTURES -DNORMALS
render normal_mapping 3 1
