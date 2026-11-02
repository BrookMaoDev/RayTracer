#!/bin/sh
g++ -O0 -g svdDynamic.c RayTracer.c utils.c -lm -pthread -o RayTracer_debug
