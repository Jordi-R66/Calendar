#include "CalendarTypes.h"
#include "CalendarIO.h"
#include "Converters.h"

InputTime arg_handler(char* argv[], int argc) {
	InputTime output;

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
	//arg_handler(argv, argc);

	//char* TIME[] = {"01/01/1970", "01:00:00"};
	char* TIME[] = {"2451545"};

	//InputTime test = parseTime(TIME, JULIAN_DAY);

	JulianDay NORAD = 25205.55836557;
	JulianDay jd = NORADToJD(NORAD, true);

	TimeStruct greg = JulianDayToGreg(jd);

	printf("%hu/%u/%u @ %u:%u:%u\n", greg.GREG_DAY, greg.GREG_MONTH, greg.GREG_YEAR, greg.HOUR, greg.MINUTE, greg.SECONDS);

	return EXIT_SUCCESS;
}