#!/bin/sh
g++ -O4 -g svdDynamic.c RayTracer.c utils.c -lm -pthread -o RayTracer
