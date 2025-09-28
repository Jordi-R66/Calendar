#include "CalendarTypes.h"
#include "CalendarIO.h"
#include "Converters.h"

ActionStruct arg_handler(char* argv[], int argc) {
	ActionStruct output;

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
						output.action = CONVERSION;
						output.timeArray[0] = parseConverter(parserArgV, parserArgC);
						break;

					case 1:
						output.action = DIFFERENCE;

						InputTime timeArray[2];

						parseDifference(parserArgV, parserArgC, timeArray);

						memcpy(output.timeArray, timeArray, sizeof(timeArray));
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

ActionResult executeAction(ActionStruct actionStruct) {
	ActionResult output;
	memset(&output, 0, ACTIONRESULT_SIZE);

	InputTime* timeArray = actionStruct.timeArray;

	switch (actionStruct.action) {
		case CONVERSION:
			generalConverter(timeArray[0].timeStruct, timeArray[0].source, timeArray[0].dest);
			break;

		default:
			break;
	}

	return output;
}

int main(int argc, char* argv[]) {
	ActionStruct actionStruct = arg_handler(argv, argc);

	printf("DATE : %hd/%u/%u @ %u:%u:%u\nUNIX : %ld\nJDAY : %.5f\n", actionStruct.timeArray[0].timeStruct.date.YEAR, actionStruct.timeArray[0].timeStruct.date.MONTH, actionStruct.timeArray[0].timeStruct.date.DAY, actionStruct.timeArray[0].timeStruct.timeOfDay.HOUR, actionStruct.timeArray[0].timeStruct.timeOfDay.MINUTE, actionStruct.timeArray[0].timeStruct.timeOfDay.SECONDS, actionStruct.timeArray[0].timeStruct.TIMESTAMP, actionStruct.timeArray[0].timeStruct.JD);

	return EXIT_SUCCESS;
}