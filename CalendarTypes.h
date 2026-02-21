#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef double JulianDay;
typedef int64_t TimeStamp;

#pragma pack(1)
typedef enum TimeFormats {
	GREGORIAN_CAL	= 0,
	JULIAN_CAL		= 1,
	HIJRI_CAL		= 2,
	JULIAN_DAY		= 3,
	UNIX_TIME		= 4,
	NORAD_TIME		= 5,
	UNKNOWN			= 255
} TimeFormats;

typedef enum Actions {
	DIFFERENCE	= 0,
	CONVERSION	= 1,
	NOW			= 2
} Actions;

typedef struct DateStruct {
	// CALENDAR
	int16_t YEAR;
	uint8_t MONTH;
	uint8_t DAY;
} DateStruct;

typedef struct TimeOfDay {
	// TIME OF THE DAY
	uint8_t HOUR;
	uint8_t MINUTE;
	uint8_t SECONDS;
} TimeOfDay;

typedef struct TimeStruct {
	DateStruct date;
	TimeOfDay timeOfDay;

	// UNIVERSAL
	TimeStamp TIMESTAMP;
	JulianDay JD, Norad;
} TimeStruct;

typedef struct CompleteTimeStruct {
	DateStruct GregDate;
	DateStruct JulianDate;
	DateStruct HijriDate;

	TimeOfDay timeOfDay;

	// UNIVERSAL
	TimeStamp TIMESTAMP;
	JulianDay JD, Norad;
} CompleteTimeStruct;

typedef struct InputTime {
	TimeStruct timeStruct;

	// Conversion instructions
	TimeFormats source, dest;
} InputTime;

typedef struct ActionStruct {
	Actions action;
	InputTime timeArray[2];
} ActionStruct;

typedef struct ActionResult {
	Actions action;
	CompleteTimeStruct result;
} ActionResult;

#pragma pack()

#define TIMESTRUCT_SIZE sizeof(TimeStruct)
#define COMPLETETIMESTRUCT_SIZE sizeof(CompleteTimeStruct)
#define INPUTTIME_SIZE sizeof(InputTime)
#define ACTIONSTRUCT_SIZE sizeof(ActionStruct)
#define ACTIONRESULT_SIZE sizeof(ActionResult)

#define TIMEFORMATS_AMOUNT 6

#define COMPARE_DS(ds1, ds2) ((ds1.YEAR == ds2.YEAR) && (ds1.MONTH == ds2.MONTH) && (ds1.DAY == ds2.DAY))
#define COMPARE_TOD(tod1, tod2) ((tod1.HOUR == tod2.HOUR) && (tod1.MINUTE == tod2.MINUTE) && (tod1.SECONDS == tod2.SECONDS))