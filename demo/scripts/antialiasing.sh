#!/bin/sh
# Same as base.sh, but with antialiasing on (16 jittered samples per pixel)
. "$(dirname "$0")/common.sh"

build antialiasing
render antialiasing 3 1
