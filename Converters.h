#pragma once

#include "projTypes.h"

// MATHEMATICAL DAY
JulianDay TimeToDayFrac(TimeStruct timeStruct);
TimeStruct DayFracToTime(JulianDay dayFrac);

// GREGORIAN
JulianDay GregToJD(TimeStruct timeStruct);
TimeStruct JulianDayToGreg(JulianDay JD);

// JULIAN
JulianDay JulianToJD(TimeStruct timeStruct);
TimeStruct JulianDayToJulian(JulianDay JD);

// UNIX TIMESTAMP
JulianDay UNIXToJD(TimeStamp unix_time);
TimeStamp JulianDayToUNIX(JulianDay JD);