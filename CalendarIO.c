#include "CalendarIO.h"

const char helpMessage[] = "The right syntax for this program is the following :\n\n\tDIFFERENCE :\n\t\tprog -d FORMAT_A TIME_A FORMAT_B TIME_B\n\n\tCONVERSION :\n\t\tprog -c SOURCE_FORMAT TIME (TARGET_FORMAT)\n\nSYNTAX FOR TIME :\nIf the selected format (or calendar) is either \"JD\" either \"UT\" the TIME argument will be an Integer for UT and a double-precision floating point number for JD.\nFor every other calendar TIME is ALWAYS composed of two separate arguments :\n\tThe first one is the date written as DD/MM/YYYY and the other one is the time of the day as hh:mm:ss using a 24hr format\n";

char* validTimeFormats[] = {
	"GC", "JC", "HC", "JD", "UT"
};

void printHelpMessage() {
	fprintf(stderr, "%s", helpMessage);
	exit(EXIT_FAILURE);
}

InputTime parseTime(char* TIME[], TimeFormats format) {
	InputTime output;

	if (format == UNKNOWN) {
		printHelpMessage();
	}

	uint8_t timeMembers = format != JULIAN_DAY && format != UNIX_TIME ? 2 : 1;

	char buffer[32];

	for (uint8_t member = 0; member < timeMembers; member++) {
		char* string = TIME[member];
		char c;

		uint8_t field;

		uint8_t i = 0;
		uint8_t index = 0;

		memset(buffer, 0, 32);

		do {
			c = string[i];

			if (c != '\0') {
				if (c == '/') {
					index = 0;

					field++;
				} else {
					buffer[index] = c;

					index++;
				}

				i++;
			} else {
				break;
			}
		} while (c != '\0'); 
	}
}

InputTime parseConverter(char* argv[], int argc) {
	InputTime output;

	uint8_t sourceIndex;

	char* endptr;

	memset(&output, 0, INPUTTIME_SIZE);

	argv = &argv[2];
	argc -= 2;

	char* source_format = argv[0];
	char* dest_format;

	// --------------------------------------------------------------------------------------------

	TimeFormats source = UNKNOWN, dest = UNKNOWN;

	for (uint8_t i = 0; i < TIMEFORMATS_AMOUNT; i++) {
		source = strcmp(source_format, validTimeFormats[i]) == 0 ? i : source;
	}

	if (source == UNKNOWN) {
		fprintf(stderr, "Unknown format for source %s\n", source_format);
		printHelpMessage();
	}

	sourceIndex = source == JULIAN_DAY || source == UNIX_TIME ? 2 : 3;

	output.convertToAll = argc != (sourceIndex + 1);
	dest_format = argc == (sourceIndex + 1) ? argv[sourceIndex] : NULL;

	for (uint8_t i = 0; i < TIMEFORMATS_AMOUNT && !output.convertToAll; i++) {
		dest = strcmp(dest_format, validTimeFormats[i]) == 0 ? i : dest;
	}

	output.source = source;
	output.dest = dest;

	InputTime parsedTime = parseTime(&argv[1], source);

	switch (source) {
		case UNIX_TIME:
			output.TIMESTAMP = parsedTime.TIMESTAMP;
			break;

		case JULIAN_DAY:
			output.JD = parsedTime.JD;
			break;

		default:
			if (source == JULIAN_CAL || source == GREGORIAN_CAL || source == HIJRI_CAL) {
				output.YEAR = parsedTime.YEAR;
				output.MONTH = parsedTime.MONTH;
				output.DAY = parsedTime.DAY;

				output.HOUR = parsedTime.HOUR;
				output.MINUTE = parsedTime.MINUTE;
				output.SECONDS = parsedTime.SECONDS;
			} else {
				printHelpMessage();
			}
			break;
	}

	return output;
}

InputTime parseDifference(char* argv[], int argc) {

}
