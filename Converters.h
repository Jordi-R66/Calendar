#pragma once

#include "CalendarTypes.h"

// MATHEMATICAL DAY
JulianDay TimeToDayFrac(TimeOfDay timeStruct);
TimeOfDay DayFracToTime(JulianDay dayFrac);

// GREGORIAN
JulianDay GregToJD(TimeStruct timeStruct);
TimeStruct JulianDayToGreg(JulianDay JD);

// JULIAN
JulianDay JulianToJD(TimeStruct timeStruct);
TimeStruct JulianDayToJulian(JulianDay JD);

// HIJRI
JulianDay HijriToJD(TimeStruct timeStruct);
TimeStruct JulianDayToHijri(JulianDay JD);

// UNIX TIMESTAMP
JulianDay UNIXToJD(TimeStamp unix_time);
TimeStamp JulianDayToUNIX(JulianDay JD);

// NORAD
JulianDay NoradToJD(JulianDay norad);
JulianDay JulianDayToNorad(JulianDay JD);

CompleteTimeStruct generalConverter(TimeStruct sourceTime, TimeFormats source, TimeFormats target);