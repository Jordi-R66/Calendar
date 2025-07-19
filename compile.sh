#!/bin/sh

mkdir -p output

gcc -g -O0 -std=c17 -fshort-enums Converters.c main.c -o output/a.out -lm
gcc -g -O0 -std=c17 -fshort-enums Converters.c main.c -S

mv *.s output/