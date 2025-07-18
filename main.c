#include "projTypes.h"

#include "Converters.h"

const char helpMessage[] = "The right syntax for this program is the following :\n\n\tDIFFERENCE :\n\t\tprog -d FORMAT_A TIME_A FORMAT_B TIME_B\n\n\tCONVERSION :\n\t\tprog -c SOURCE_FORMAT TIME (TARGET_FORMAT)\n\nSYNTAX FOR TIME :\nIf the selected format (or calendar) is either \"JD\" either \"UT\" the TIME argument will be an Integer for UT and a double-precision floating point number for JD.\nFor every other calendar TIME is composed of two separate arguments :\n\tThe first one is the date written as DD/MM/YYYY and the other one is the time of the day as hh:mm:ss using a 24hr format\n";

void printHelpMessage() {
	fprintf(stderr, "%s", helpMessage);
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {

	JulianDay J2000 = GregToJD((TimeStruct){.GREG_DAY = 4, .GREG_MONTH = 1, .GREG_YEAR = 1643, .HOUR = 0});
	TimeStruct J2000_J = JulianDayToJulian(J2000);

	printf("%u/%u/%lu @ %u:%u:%u\n", J2000_J.JULIAN_DAY, J2000_J.JULIAN_MONTH, J2000_J.JULIAN_YEAR, J2000_J.HOUR, J2000_J.MINUTE, J2000_J.SECONDS);

	return EXIT_SUCCESS;
}