#include "CalendarIO.h"

const char helpMessage[] = "The right syntax for this program is the following :\n\n  DIFFERENCE :\n    prog -d FORMAT_A TIME_A FORMAT_B TIME_B\n\n  CONVERSION :\n    prog -c SOURCE_FORMAT TIME (TARGET_FORMAT)\n\nSYNTAX FOR TIME :\nIf the selected format (or calendar) is either \"JD\" either \"UT\" the TIME argument will be an Integer for UT and a double-precision floating point number for JD.\nFor every other calendar TIME is ALWAYS composed of two separate arguments :\n  The first one is the date written as DD/MM/YYYY and the other one is the time of the day as hh:mm:ss using a 24hr format\n";

char* validTimeFormats[] = {
	"GC", "JC", "HC", "JD", "UT"
};

void printHelpMessage(void) {
	fprintf(stderr, "%s", helpMessage);
	exit(EXIT_FAILURE);
}

void parseFields(long fields[], uint8_t fields_number, char* string, char sep) {
	char buffer[32];

	memset(buffer, 0, 32);

	char end;
	char* endptr;

	uint8_t field = 0;
	uint8_t j = 0;

	size_t string_size = strlen(string);

	for (size_t i = 0; (i <= string_size) && (field < fields_number); i++) {
		char c = string[i];

		if (c == sep || c == '\0') {
			fields[field] = strtol(buffer, &endptr, 10);
			memset(buffer, 0, j);

			field++;
			j = 0;
		} else {
			if ((('0' <= c) && (c <= '9')) || (c == '-')) {
				buffer[j++] = c;
			}
		}
	}
}

TimeStruct parseDDMMYYYY(char* date) {
	TimeStruct output;

	long fields[3];

	parseFields(fields, 3, date, '/');

	if (fields[0] < 0) {
		fprintf(stderr, "You provided a negative day\n");
		exit(EXIT_FAILURE);
	}

	if (fields[1] < 0) {
		fprintf(stderr, "You provided a negative month\n");
		exit(EXIT_FAILURE);
	}

	memset(&output, 0, TIMESTRUCT_SIZE);

	if (fields[0] < 256) {
		output.DAY = (uint8_t)fields[0];
	} else {
		fprintf(stderr, "Value out of range.\n");
		exit(EXIT_FAILURE);
	}

	if (fields[1] < 256) {
		output.MONTH = (uint8_t)fields[1];
	} else {
		fprintf(stderr, "Value out of range.\n");
		exit(EXIT_FAILURE);
	}

	if ((-32768 <= fields[2]) && (fields[2] < 32768)) {
		output.YEAR = (int16_t)fields[2];
	} else {
		fprintf(stderr, "Value out of range.\n");
		exit(EXIT_FAILURE);
	}

	return output;
}

TimeStruct parseHHMMSS(char* timeOfDay) {
	TimeStruct output;

	long fields[3];

	parseFields(fields, 3, timeOfDay, ':');

	if (fields[0] < 0) {
		fprintf(stderr, "You provided a negative hour\n");
		exit(EXIT_FAILURE);
	}

	if (fields[1] < 0) {
		fprintf(stderr, "You provided a negative minute\n");
		exit(EXIT_FAILURE);
	}

	if (fields[2] < 0) {
		fprintf(stderr, "You provided a negative second\n");
		exit(EXIT_FAILURE);
	}

	memset(&output, 0, TIMESTRUCT_SIZE);

	if (fields[0] < 24) {
		output.HOUR = (uint8_t)fields[0];
	} else {
		fprintf(stderr, "Value out of range.\n");
		exit(EXIT_FAILURE);
	}

	if (fields[1] < 60) {
		output.MINUTE = (uint8_t)fields[1];
	} else {
		fprintf(stderr, "Value out of range.\n");
		exit(EXIT_FAILURE);
	}

	if (fields[2] < 60) {
		output.SECONDS = (uint8_t)fields[2];
	} else {
		fprintf(stderr, "Value out of range.\n");
		exit(EXIT_FAILURE);
	}

	return output;
}

TimeStruct parseTime(char* timeString, TimeFormats format) {
	TimeStruct output;

	char end;
	char* endptr;

	memset(&output, 0, TIMESTRUCT_SIZE);

	switch (format) {
		case JULIAN_DAY:
			output.JD = strtod(timeString, &endptr);
			break;

		case UNIX_TIME:
			output.TIMESTAMP = strtol(timeString, &endptr, 10);
			break;

		default:
			fprintf(stderr, "An error happened.\n");
			exit(EXIT_FAILURE);
			break;
	}

	return output;
}

InputTime parseConverter(char* argv[], int argc) {
	/*
		IF SOURCE_FORMAT IN ("JD", "UT") THEN
			SOURCE_FORMAT TIME (TARGET_FORMAT)
		ELSE
			SOURCE_FORMAT DATE TIME (TARGET_FORMAT)
		END IF
	*/

	char* TIME[2];
	InputTime output = {.timeStruct = {0, 0, 0, 0, 0, 0, 0, 0}, false, UNKNOWN, UNKNOWN};

	uint8_t inputIndex = 0, outputIndex = argc - 1;
	uint8_t dateIndex = inputIndex + 1, timeIndex = dateIndex + 1;

	bool sourceIsCalendar = false;
	bool targetIsKnown = false;

	char* inputFormat = argv[0];
	char* outputFormat = argv[argc-1];

	for (uint8_t i = 0; i < TIMEFORMATS_AMOUNT; i++) {
		if (strcmp(inputFormat, validTimeFormats[i]) == 0) {
			output.source = (TimeFormats)i;
			sourceIsCalendar = output.source < 3;
		}

		if (strcmp(outputFormat, validTimeFormats[i]) == 0) {
			output.dest = (TimeFormats)i;
			targetIsKnown = true;
		}
	}

	if (output.source != UNKNOWN) {
		printf("Source format : %s\n", validTimeFormats[output.source]);
	} else {
		fprintf(stderr, "Couldn't identify source format '%s'\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	bool isArgCountValid =	(sourceIsCalendar && !targetIsKnown && (argc == 3)) ^
							(sourceIsCalendar && targetIsKnown && (argc == 4)) ^
							(!sourceIsCalendar && !targetIsKnown && (argc == 2)) ^
							(!sourceIsCalendar && targetIsKnown && (argc == 3));

	if (!isArgCountValid) {
		fprintf(stderr, "You did not provide the right amount of arguments\n");
		printHelpMessage();
	}

	TimeStruct parsed;

	if (sourceIsCalendar) {
		parsed = parseDDMMYYYY(argv[dateIndex]);
		TimeStruct timeOfDay = parseHHMMSS(argv[timeIndex]);

		parsed.HOUR = timeOfDay.HOUR;
		parsed.MINUTE = timeOfDay.MINUTE;
		parsed.SECONDS = timeOfDay.SECONDS;
	} else {
		parsed = parseTime(argv[dateIndex], output.source);
	}

	output.timeStruct = parsed;

	return output;
}

InputTime parseDifference(char* argv[], int argc) {

}
