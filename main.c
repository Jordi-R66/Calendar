#include "projTypes.h"

#define MODES_AMOUNT 3
#define TIMEFORMATS_AMOUT 5

#include "Converters.h"

const char helpMessage[] = "The right syntax for this program is the following :\n\n\tDIFFERENCE :\n\t\tprog -d FORMAT_A TIME_A FORMAT_B TIME_B\n\n\tCONVERSION :\n\t\tprog -c SOURCE_FORMAT TIME (TARGET_FORMAT)\n\nSYNTAX FOR TIME :\nIf the selected format (or calendar) is either \"JD\" either \"UT\" the TIME argument will be an Integer for UT and a double-precision floating point number for JD.\nFor every other calendar TIME is composed of two separate arguments :\n\tThe first one is the date written as DD/MM/YYYY and the other one is the time of the day as hh:mm:ss using a 24hr format\n";

char* validTimeFormats[] = {
	"GC", "JC", "HC", "JD", "UT"
};

void printHelpMessage() {
	fprintf(stderr, "%s", helpMessage);
	exit(EXIT_FAILURE);
}

SimpleTime parseConverter(char* argv[], int argc);
SimpleTime parseDifference(char* argv[], int argc);

SimpleTime arg_handler(char* argv[], int argc) {
	SimpleTime output;

	char* validModeArgs[] = {
		"-c", "-d", "-h"
	};

	TimeFormats FormatA, FormatB;

	bool invalidArgs = false;

	if (argc < 2) {
		invalidArgs = true;
	} else {
		for (uint8_t i = 0; i < MODES_AMOUNT; i++) {
			if (strcmp(argv[1], validModeArgs[i]) == 0) {
				switch (i) {
					case 0:
						output = parseConverter(argv, argc);
						break;

					case 1:
						output = parseDifference(argv, argc);
						break;

					case 2:
						fprintf(stderr, "Here's the help you asked for!\n\n");
						printHelpMessage();

					default:
						invalidArgs = true;
						break;
				}
			}
		}
	}

	if (invalidArgs) {
		fprintf(stderr, "Invalid args detected\n");
		printHelpMessage();
	}

	return output;
}

int main(int argc, char* argv[]) {

	JulianDay J2000 = GregToJD((TimeStruct){.GREG_DAY = 4, .GREG_MONTH = 1, .GREG_YEAR = 1643, .HOUR = 0});
	TimeStruct J2000_J = JulianDayToJulian(J2000);

	printf("%u/%u/%lu @ %u:%u:%u\n", J2000_J.JULIAN_DAY, J2000_J.JULIAN_MONTH, J2000_J.JULIAN_YEAR, J2000_J.HOUR, J2000_J.MINUTE, J2000_J.SECONDS);

	return EXIT_SUCCESS;
}