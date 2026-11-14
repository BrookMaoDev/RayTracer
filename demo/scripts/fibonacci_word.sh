#!/bin/sh
# Separate scene: the Fibonacci word fractal (0 -> 01, 1 -> 0), drawn as a path of steps and turns
. "$(dirname "$0")/common.sh"

build fibonacci_word -DSCENE_FIBONACCI
render fibonacci_word 10 1
