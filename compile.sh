#!/bin/sh

mkdir -p output

gcc -s -O3 -masm=intel -std=gnu17 -fshort-enums CalendarIO.c Converters.c main.c -o output/calendar.out -lm
gcc -s -O3 -masm=intel -std=gnu17 -fshort-enums CalendarIO.c Converters.c main.c -S

mv *.s output/