#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef double JulianDay;
typedef int64_t TimeStamp;

typedef struct {
	// GREGORIAN CALENDAR
	int64_t GREG_YEAR;
	uint8_t GREG_MONTH;
	uint8_t GREG_DAY;

	// JULIAN CALENDAR
	int64_t JULIAN_YEAR;
	uint8_t JULIAN_MONTH;
	uint8_t JULIAN_DAY;

	// TIME OF THE DAY
	uint8_t HOUR;
	uint8_t MINUTE;
	uint8_t SECONDS;

	// UNIVERSAL
	TimeStamp TIMESTAMP;
	JulianDay JD;
} TimeStruct;