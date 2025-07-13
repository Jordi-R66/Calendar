#include "Converters.h"

#include <math.h>

const uint64_t NAN_INT = 0b0111111111110000000000000000000000000000000000000000000000000001L;

const TimeStruct UNIX_0_TS = { .GREG_YEAR = 1970, .GREG_MONTH = 1, .GREG_DAY = 1 };

// NEEDED

double ENT(double x) {
	return floor(x);
}

double TRONQ(double x) {
	return trunc(x);
}

double FRAC(double x) {
	return x - TRONQ(x);
}

// MATHEMATICAL DAY

JulianDay TimeToDayFrac(TimeStruct timeStruct) {
	int8_t H = timeStruct.HOUR,
		M = timeStruct.MINUTE,
		S = timeStruct.SECONDS;

	if (H >= 24 || M >= 60 || S >= 60) {
		return *(JulianDay*)&NAN_INT;
	}

	return (JulianDay)(H * 3600 + M * 60 + S) / 86400.0;
}

TimeStruct DayFracToTime(JulianDay dayFrac) {
	uint32_t asSeconds = (uint32_t)(dayFrac * 86400.0);

	uint8_t H, M, S;

	H = asSeconds / 3600;
	asSeconds %= 3600;

	M = asSeconds / 60;
	asSeconds %= 60;

	S = asSeconds;

	TimeStruct output = { .HOUR = H, .MINUTE = M, .SECONDS = S };

	return output;
}

// GREGORIAN CALENDAR

JulianDay GregToJD(TimeStruct timeStruct) {
	uint64_t YEAR = timeStruct.GREG_YEAR;
	uint8_t MONTH = timeStruct.GREG_MONTH, DAY = timeStruct.GREG_DAY;

	if (MONTH == 1 || MONTH == 2) {
		YEAR--;
		MONTH += 12;
	}

	double S = ENT((double)YEAR / 100.0);
	double B = 2.0 - S + ENT(S / 4.0);

	return ENT(365.25 * YEAR) + ENT(30.6001 * (MONTH + 1)) + DAY + TimeToDayFrac(timeStruct) + B + 1720994.5;
}

TimeStruct JulianDayToGreg(JulianDay JD) {
	double Z = ENT(JD);
	double F = FRAC(JD+.5);

	double alpha = ENT((Z - 1867216.25) / 36524.25);
	double S = Z + 1.0 + alpha - ENT(alpha / 4.0);

	double B = S + 1524.0;
	int64_t C = (int64_t)ENT((B - 122.1) / 365.25);
	double D = ENT(365.25 * C);
	double E = ENT((B - D) / 30.6001);

	uint8_t DAY = B - D - ENT(30.6001 * E);
	uint8_t MONTH = E < 14 ? E - 1.0 : E - 13.0;

	int64_t YEAR = MONTH > 2 ? C - 4716 : C - 4715;

	TimeStruct fracStruct = DayFracToTime(F);

	return (TimeStruct) { .GREG_DAY = DAY, .GREG_MONTH = MONTH, .GREG_YEAR = YEAR, .HOUR = fracStruct.HOUR, .MINUTE = fracStruct.MINUTE, .SECONDS = fracStruct.SECONDS, .JD = JD, .TIMESTAMP = JulianDayToUNIX(JD) };
}

// JULIAN
JulianDay JulianToJD(TimeStruct timeStruct) {
	uint64_t YEAR = timeStruct.JULIAN_YEAR;
	uint8_t MONTH = timeStruct.JULIAN_MONTH, DAY = timeStruct.JULIAN_DAY;

	if (MONTH == 1 || MONTH == 2) {
		YEAR--;
		MONTH += 12;
	}

	return ENT((1461.0 * (JulianDay)YEAR + 6884472.0) / 4.0) + ENT((153.0 * MONTH - 457.0) / 5.0) + (JulianDay)DAY + TimeToDayFrac(timeStruct) - 1;
}

TimeStruct JulianDayToJulian(JulianDay JD) {
	int64_t YEAR = (int64_t)ENT((4.0 * JD - 6884469.0) / 1461.0);
	double R2 = JD - ENT((1461.0 * (JulianDay)YEAR + 6884472.0) / 4.0);

	uint8_t MONTH = (uint8_t)ENT((5.0 * R2 + 461.0) / 153.0);
	double R1 = R2 - ENT((153.0 * (JulianDay)MONTH - 457.0) / 5.0);

	double Q = R1 + 1.0 +.5;
	uint8_t DAY = (uint8_t)ENT(Q);

	if (MONTH == 13 || MONTH == 14) {
		YEAR++;
		MONTH -= 12;
	}

	TimeStruct fracStruct = DayFracToTime(FRAC(Q));

	return (TimeStruct) { .JULIAN_DAY = DAY, .JULIAN_MONTH = MONTH, .JULIAN_YEAR = YEAR, .HOUR = fracStruct.HOUR, .MINUTE = fracStruct.MINUTE, .SECONDS = fracStruct.SECONDS, .JD = JD, .TIMESTAMP = JulianDayToUNIX(JD) };
}

// UNIX TIMESTAMP

JulianDay UNIXToJD(TimeStamp unix_time) {
	JulianDay output = GregToJD(UNIX_0_TS);

	return output + (JulianDay)unix_time / 86400.0;
}

TimeStamp JulianDayToUNIX(JulianDay JD) {
	JulianDay UNIX_0_JD = UNIXToJD(0);

	return (TimeStamp)((JD - UNIX_0_JD) * 86400.0);
}