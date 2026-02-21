#include "Converters.h"

#include <math.h>

const TimeStruct UNIX_0_TS_GC = {
	.date = {.YEAR = 1970, .MONTH = 1, .DAY = 1}
};

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

JulianDay TimeToDayFrac(TimeOfDay timeOfDay) {
	int8_t H = timeOfDay.HOUR,
		M = timeOfDay.MINUTE,
		S = timeOfDay.SECONDS;

	if (H >= 24 || M >= 60 || S >= 60) {
		return nan("");
	}

	return (JulianDay)(H * 3600 + M * 60 + S) / 86400.0;
}

TimeOfDay DayFracToTime(JulianDay dayFrac) {
	TimeStamp asSeconds = (TimeStamp)round(dayFrac * 86400.0);

	uint8_t H, M, S;

	H = asSeconds / 3600;
	asSeconds %= 3600;

	M = asSeconds / 60;
	asSeconds %= 60;

	S = asSeconds;

	TimeOfDay output = { .HOUR = H, .MINUTE = M, .SECONDS = S };

	return output;
}

#pragma region Gregorian Calendar

JulianDay GregToJD(TimeStruct timeStruct) {
	int16_t YEAR = timeStruct.date.YEAR;
	uint8_t MONTH = timeStruct.date.MONTH, DAY = timeStruct.date.DAY;

	if (MONTH == 1 || MONTH == 2) {
		YEAR--;
		MONTH += 12;
	}

	double S = ENT((double)YEAR / 100.0);
	double B = 2.0 - S + ENT(S / 4.0);

	return ENT(365.25 * YEAR) + ENT(30.6001 * (MONTH + 1)) + DAY + TimeToDayFrac(timeStruct.timeOfDay) + B + 1720994.5 + .5;
}

TimeStruct JulianDayToGreg(JulianDay JD) {
	double Z = ENT(JD);
	double F = FRAC(JD);

	double alpha = ENT((Z - 1867216.25) / 36524.25);
	double S = Z + 1.0 + alpha - ENT(alpha / 4.0);

	double B = S + 1524.0;
	int16_t C = (int16_t)ENT((B - 122.1) / 365.25);
	double D = ENT(365.25 * C);
	double E = ENT((B - D) / 30.6001);

	uint8_t DAY = B - D - ENT(30.6001 * E);
	uint8_t MONTH = E < 14 ? E - 1.0 : E - 13.0;

	int16_t YEAR = MONTH > 2 ? C - 4716 : C - 4715;

	TimeOfDay fracStruct = DayFracToTime(FRAC(F));

	return (TimeStruct) {
		.date = { YEAR, MONTH, DAY },
			.timeOfDay = { fracStruct.HOUR, fracStruct.MINUTE, fracStruct.SECONDS },
			.JD = JD,
			.TIMESTAMP = JulianDayToUNIX(JD)
	};
}

#pragma endregion

#pragma region Julian Calendar

JulianDay JulianToJD(TimeStruct timeStruct) {
	int16_t YEAR = timeStruct.date.YEAR;
	uint8_t MONTH = timeStruct.date.MONTH, DAY = timeStruct.date.DAY;

	if (MONTH == 1 || MONTH == 2) {
		YEAR--;
		MONTH += 12;
	}

	return ENT((1461.0 * (JulianDay)YEAR + 6884472.0) / 4.0) + ENT((153.0 * MONTH - 457.0) / 5.0) + (JulianDay)DAY + TimeToDayFrac(timeStruct.timeOfDay) - 1;
}

TimeStruct JulianDayToJulian(JulianDay JD) {
	int16_t YEAR = (int16_t)ENT((4.0 * JD - 6884469.0) / 1461.0);
	double R2 = JD - ENT((1461.0 * (JulianDay)YEAR + 6884472.0) / 4.0);

	uint8_t MONTH = (uint8_t)ENT((5.0 * R2 + 461.0) / 153.0);
	double R1 = R2 - ENT((153.0 * (JulianDay)MONTH - 457.0) / 5.0);

	double Q = R1 + 1.0;
	uint8_t DAY = (uint8_t)ENT(Q);

	if (MONTH == 13 || MONTH == 14) {
		YEAR++;
		MONTH -= 12;
	}

	TimeOfDay fracStruct = DayFracToTime(FRAC(Q));

	return (TimeStruct) {
		.date = { YEAR, MONTH, DAY },
			.timeOfDay = { fracStruct.HOUR, fracStruct.MINUTE, fracStruct.SECONDS },
			.JD = JD,
			.TIMESTAMP = JulianDayToUNIX(JD)
	};
}

#pragma endregion

#pragma region Hijri Calendar

JulianDay HijriToJD(TimeStruct timeStruct) {
	uint16_t YEAR = timeStruct.date.YEAR;
	uint8_t MONTH = timeStruct.date.MONTH, DAY = timeStruct.date.DAY;

	return TRONQ((10631.0 * (JulianDay)YEAR + 58442583.0) / 30.0) + TRONQ((325.0 * (JulianDay)MONTH - 320.0) / 11.0) + (JulianDay)DAY + TimeToDayFrac(timeStruct.timeOfDay) - 1.0;
}

TimeStruct JulianDayToHijri(JulianDay JD) {
	int16_t YEAR = (int16_t)TRONQ((30.0 * JD - 58442554.0) / 10631.0);
	double R2 = JD - TRONQ((10631.0 * (JulianDay)YEAR + 58442583.0) / 30.0);

	uint8_t MONTH = (uint8_t)TRONQ((11.0 * R2 + 330.0) / 325.0);
	double R1 = R2 - TRONQ((325.0 * (JulianDay)MONTH - 320.0) / 11.0);

	double Q = R1 + 1.0;
	uint8_t DAY = (uint8_t)ENT(Q);

	TimeOfDay fracStruct = DayFracToTime(FRAC(Q));

	return (TimeStruct) {
		.date = { YEAR, MONTH, DAY },
			.timeOfDay = { fracStruct.HOUR, fracStruct.MINUTE, fracStruct.SECONDS },
			.JD = JD,
			.TIMESTAMP = JulianDayToUNIX(JD)
	};
}

#pragma endregion

#pragma region Unix Timestamp

JulianDay UNIXToJD(TimeStamp unix_time) {
	JulianDay output = GregToJD(UNIX_0_TS_GC);

	return output + (JulianDay)unix_time / 86400.0;
}

TimeStamp JulianDayToUNIX(JulianDay JD) {
	JulianDay UNIX_0_JD = UNIXToJD(0);

	JulianDay DeltaJD = JD - UNIX_0_JD;

	TimeStamp jdAsTimeStamp = (TimeStamp)round(FRAC(DeltaJD) * 86400.0) + 86400 * (TimeStamp)ENT(DeltaJD);

	return jdAsTimeStamp;
}

#pragma endregion

#pragma region Norad Timestamp

JulianDay NoradToJD(JulianDay norad) {
	JulianDay JD = 0.0, tempJD = norad - 1.0;
	uint32_t int_jd = (uint32_t)norad - 1;

	int16_t year = ((int16_t)int_jd) / 1000;

	tempJD -= (double)(year * 1000);
	year += (year < 57) ? 2000 : 1900;

	TimeStruct temp = {
		.date = {.DAY = 1, .MONTH = 1, .YEAR = year},
		.timeOfDay = {.HOUR = 0.0, .MINUTE = 0.0, .SECONDS = 0.0},
		.JD = 0.0,
		.TIMESTAMP = 0,
		.Norad = 0.0
	};

	JD += GregToJD(temp) + tempJD;

	return JD;
}

JulianDay JulianDayToNorad(JulianDay JD) {
	JulianDay norad = 1.0;

	TimeStruct greg = JulianDayToGreg(JD);
	TimeStruct temp = {
		.date = {.DAY = 1, .MONTH = 1, .YEAR = greg.date.YEAR},
		.timeOfDay = {.HOUR = 0.0, .MINUTE = 0.0, .SECONDS = 0.0},
		.JD = 0.0,
		.TIMESTAMP = 0,
		.Norad = 0.0
	};

	double year = (double)(greg.date.YEAR % 100) * 1000.0;

	norad += year + (JD - GregToJD(temp));

	return norad;
}


CompleteTimeStruct JulianDayToAny(JulianDay JD, TimeFormats target) {
	CompleteTimeStruct output;

	memset(&output, 0, COMPLETETIMESTRUCT_SIZE);

	TimeStruct converted;

	if (target >= TIMEFORMATS_AMOUNT) {
		exit(EXIT_FAILURE);
	}

	switch (target) {
		case GREGORIAN_CAL:
			converted = JulianDayToGreg(JD);
			output.GregDate = converted.date;
			break;

		case JULIAN_CAL:
			converted = JulianDayToJulian(JD);
			output.JulianDate = converted.date;
			break;

		case HIJRI_CAL:
			converted = JulianDayToHijri(JD);
			output.HijriDate = converted.date;
			break;

		case JULIAN_DAY:
			output.JD = JD;
			break;

		case UNIX_TIME:
			output.TIMESTAMP = JulianDayToUNIX(JD);
			break;

		case NORAD_TIME:
			output.Norad = JulianDayToNorad(JD);
			break;

	default:
		exit(EXIT_FAILURE);
		break;
	}

	if (target < 3) {
		output.timeOfDay = converted.timeOfDay;
	}

	return output;
}

CompleteTimeStruct generalConverter(TimeStruct sourceTime, TimeFormats source, TimeFormats target) {
	JulianDay intermediate;
	CompleteTimeStruct output;

	memset(&output, 0, COMPLETETIMESTRUCT_SIZE);

	// Getting rid of the situation where source = target
	if (source == target) {
		switch (source) {
		case GREGORIAN_CAL:
			output.GregDate = sourceTime.date;
			output.timeOfDay = sourceTime.timeOfDay;
			break;

		case JULIAN_CAL:
			output.JulianDate = sourceTime.date;
			output.timeOfDay = sourceTime.timeOfDay;
			break;

		case HIJRI_CAL:
			output.HijriDate = sourceTime.date;
			output.timeOfDay = sourceTime.timeOfDay;
			break;

		case UNIX_TIME:
			output.TIMESTAMP = sourceTime.TIMESTAMP;
			break;

		case JULIAN_DAY:
			output.JD = sourceTime.JD;
			break;

		case NORAD_TIME:
			output.Norad = sourceTime.Norad;
			break;

		default:
			exit(EXIT_FAILURE);
			break;
		}

		return output;
	}

	switch (source) {
	case GREGORIAN_CAL:
		intermediate = GregToJD(sourceTime);
		break;

	case JULIAN_CAL:
		intermediate = JulianToJD(sourceTime);
		break;

	case HIJRI_CAL:
		intermediate = HijriToJD(sourceTime);
		break;

	case UNIX_TIME:
		intermediate = UNIXToJD(sourceTime.TIMESTAMP);
		break;

	case JULIAN_DAY:
		intermediate = sourceTime.JD;
		break;

	case NORAD_TIME:
		intermediate = NoradToJD(sourceTime.Norad);
		break;

	default:
		exit(EXIT_FAILURE);
		break;
	}

	for (TimeFormats format = 0; format < TIMEFORMATS_AMOUNT; format++) {
		CompleteTimeStruct temp = JulianDayToAny(intermediate, format);

		if ((target != UNKNOWN) && (format == target)) {
			output = temp;
			break;
		}
		else if (target == UNKNOWN) {
			switch (format) {
			case GREGORIAN_CAL:
				output.GregDate = temp.GregDate;
				output.timeOfDay = temp.timeOfDay;
				break;

			case JULIAN_CAL:
				output.JulianDate = temp.JulianDate;
				output.timeOfDay = temp.timeOfDay;
				break;

			case HIJRI_CAL:
				output.HijriDate = temp.HijriDate;
				output.timeOfDay = temp.timeOfDay;
				break;

			case JULIAN_DAY:
				output.JD = temp.JD;
				break;

			case UNIX_TIME:
				output.TIMESTAMP = temp.TIMESTAMP;
				break;

			case NORAD_TIME:
				output.Norad = temp.Norad;
				break;

			default:
				exit(EXIT_FAILURE);
				break;
			}
		}
	}

	return output;
}
