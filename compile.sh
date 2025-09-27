#!/bin/sh

mkdir -p output

gcc -g -O0 -std=c17 -fshort-enums CalendarIO.c Converters.c main.c -o output/calendar.out -lm
gcc -g -O0 -std=c17 -fshort-enums CalendarIO.c Converters.c main.c -S

mv *.s output/