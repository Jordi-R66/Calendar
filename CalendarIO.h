#pragma once

#include "CalendarTypes.h"

#define MODES_AMOUNT 3

extern const char helpMessage[];
extern char* validTimeFormats[];

void printHelpMessage(void);
void parseFields(long fields[], uint8_t fields_number, char* string, char sep);
DateStruct parseDDMMYYYY(char* date);
TimeOfDay parseHHMMSS(char* timeOfDay);
TimeStruct parseTime(char* timeString, TimeFormats format);
InputTime parseConverter(char* argv[], int argc);
void parseDifference(char* argv[], int argc, InputTime timeArray[2]);

void printTimeStruct(TimeStruct date, TimeFormats format);