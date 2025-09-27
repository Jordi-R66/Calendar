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
		char** parserArgV = &argv[2];
		int parserArgC = argc - 2;

		for (uint8_t i = 0; i < MODES_AMOUNT; i++) {
			if (strcmp(argv[1], validModeArgs[i]) == 0) {
				switch (i) {
					case 0:
						output = parseConverter(parserArgV, parserArgC);
						break;

					case 1:
						output = parseDifference(parserArgV, parserArgC);
						break;

					case 2:
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
	InputTime time = arg_handler(argv, argc);

	printf("DATE : %hd/%u/%u @ %u:%u:%u\nUNIX : %ld\nJDAY : %.5f\n", time.timeStruct.YEAR, time.timeStruct.MONTH, time.timeStruct.DAY, time.timeStruct.HOUR, time.timeStruct.MINUTE, time.timeStruct.SECONDS, time.timeStruct.TIMESTAMP, time.timeStruct.JD);

	return EXIT_SUCCESS;
}