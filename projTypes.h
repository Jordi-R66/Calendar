#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef double JulianDay;
typedef int64_t TimeStamp;

#pragma pack(1)
typedef enum {
	GREGORIAN_CAL = 0,
	JULIAN_CAL = 1,
	HIJRI_CAL = 2,
	JULIAN_DAY = 3,
	UNIX_TIME = 4
} TimeFormats;

typedef struct {
	int64_t YEAR;
	uint8_t MONTH;
	uint8_t DAY;

	uint8_t HOUR;
	uint8_t MINUTE;
	uint8_t SECONDS;

	// UNIVERSAL
	TimeStamp TIMESTAMP;
	JulianDay JD;
} SimpleTime;

typedef struct {
	// GREGORIAN CALENDAR
	int64_t GREG_YEAR;
	uint8_t GREG_MONTH;
	uint8_t GREG_DAY;

	// JULIAN CALENDAR
	int64_t JULIAN_YEAR;
	uint8_t JULIAN_MONTH;
	uint8_t JULIAN_DAY;

	// HIJRI CALENDAR
	int64_t HIJRI_YEAR;
	uint8_t HIJRI_MONTH;
	uint8_t HIJRI_DAY;

	// TIME OF THE DAY
	uint8_t HOUR;
	uint8_t MINUTE;
	uint8_t SECONDS;

	// UNIVERSAL
	TimeStamp TIMESTAMP;
	JulianDay JD;
} TimeStruct;
#pragma pack()

#define TIMESTRUCT_SIZE sizeof(TimeStruct)
#define SIMPLETIME_SIZE sizeof(SimpleTime)