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

// HIJRI
JulianDay HijriToJD(TimeStruct timeStruct);
TimeStruct JulianDayToHijri(JulianDay JD);

// UNIX TIMESTAMP
JulianDay UNIXToJD(TimeStamp unix_time);
TimeStamp JulianDayToUNIX(JulianDay JD);

// NORAD
JulianDay NORADToJD(JulianDay norad, bool cropped);
JulianDay JDToNORAD(JulianDay JD, bool cropped);