#include "CalendarTypes.h"
#include "CalendarIO.h"
#include "Converters.h"

#include <time.h>

ActionStruct arg_handler(char* argv[], int argc) {
	ActionStruct output;

	char* validModeArgs[] = {
		"-h", "-d", "-c", "-n"
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
						printHelpMessage();

					case 1:
						output.action = DIFFERENCE;

						InputTime timeArray[2];

						parseDifference(parserArgV, parserArgC, timeArray);

						memcpy(output.timeArray, timeArray, 2 * INPUTTIME_SIZE);
						break;

					case 2:
						output.action = CONVERSION;
						output.timeArray[0] = parseConverter(parserArgV, parserArgC);
						break;

					case 3:
						output.action = CONVERSION;

						output.timeArray[0] = (InputTime){
							.timeStruct = { .TIMESTAMP = time(NULL) },
							.source = UNIX_TIME,
							.dest = UNKNOWN
						};

						if (argc == 3) {
							char* stringFormat = argv[2];

							for (uint8_t i = 0; i < TIMEFORMATS_AMOUNT; i++) {
								if (strcmp(stringFormat, validTimeFormats[i]) == 0) {
									output.timeArray[0].dest = (TimeFormats)i;
								}
							}

							if (output.timeArray[0].dest == UNKNOWN) {
								invalidArgs = true;
								break;
							}
						} else if (argc > 3) {
							invalidArgs = true;
							break;
						}

						break;

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

	output.action = actionStruct.action;

	switch (actionStruct.action) {
		case CONVERSION:
			output.result = generalConverter(timeArray[0].timeStruct, timeArray[0].source, timeArray[0].dest);
			break;

		default:
			break;
	}

	return output;
}

int main(int argc, char* argv[]) {
	ActionStruct actionStruct = arg_handler(argv, argc);

	ActionResult result = executeAction(actionStruct);

	switch (actionStruct.action) {
		case CONVERSION:
			TimeFormats srcFormat, destFormat;
			InputTime time = actionStruct.timeArray[0];

			srcFormat = time.source;
			destFormat = time.dest;

			if (destFormat == UNKNOWN) {
				printCompleteTimeStruct(result.result);
			} else {
				TimeStruct time_struct = extractFromCompleteTimeStruct(result.result, time.dest);

				printTimeStruct(time_struct, time.dest);
				fprintf(stdout, "\n");
			}

		default:
			break;
	}

	return EXIT_SUCCESS;
}