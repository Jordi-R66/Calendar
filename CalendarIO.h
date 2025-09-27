#pragma once

#include "CalendarTypes.h"

#define MODES_AMOUNT 3
#define TIMEFORMATS_AMOUNT 5

extern const char helpMessage[];
extern char* validTimeFormats[];

void printHelpMessage(void);
void parseFields(long fields[], uint8_t fields_number, char* string, char sep);
TimeStruct parseDDMMYYYY(char* date);
TimeStruct parseHHMMSS(char* timeOfDay);
TimeStruct parseTime(char* timeString, TimeFormats format);
InputTime parseConverter(char* argv[], int argc);
InputTime parseDifference(char* argv[], int argc);
