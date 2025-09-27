#pragma once

#include "CalendarTypes.h"

#define MODES_AMOUNT 3
#define TIMEFORMATS_AMOUNT 5

extern const char helpMessage[];
extern char* validTimeFormats[];

void printHelpMessage();
InputTime parseTime(char* TIME[], TimeFormats format);
InputTime parseConverter(char* argv[], int argc);
InputTime parseDifference(char* argv[], int argc);
