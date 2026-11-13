#!/bin/sh
# Shared setup for the demo scripts (sourced, not run directly).
#   build NAME [FLAGS...]  compiles the ray tracer with the given -D flags into demo/bin/NAME
#   render NAME DEPTH AA   renders demo/renderings/NAME.ppm at SIZE x SIZE with that binary
set -e
cd "$(dirname "$0")/../.."	# Repo root: the scene loads textures from ./textures
mkdir -p demo/bin demo/renderings

SIZE=1024

build() {
  name=$1
  shift
  g++ -O4 svdDynamic.c RayTracer.c utils.c -lm -pthread "$@" -o "demo/bin/$name"
}

render() {
  start=$(date +%s)
  "./demo/bin/$1" "$SIZE" "$2" "$3" "demo/renderings/$1.ppm"
  echo "$1: rendered demo/renderings/$1.ppm in $(( $(date +%s) - start ))s"
}
