#include "projTypes.h"

#include "Converters.h"

void arg_handler(char* argv[], int argc);

int main(int argc, char* argv[]) {

	JulianDay J2000 = GregToJD((TimeStruct){.GREG_DAY = 4, .GREG_MONTH = 1, .GREG_YEAR = 1643, .HOUR = 0});
	TimeStruct J2000_J = JulianDayToJulian(J2000);

	printf("%u/%u/%lu @ %u:%u:%u\n", J2000_J.JULIAN_DAY, J2000_J.JULIAN_MONTH, J2000_J.JULIAN_YEAR, J2000_J.HOUR, J2000_J.MINUTE, J2000_J.SECONDS);

	return EXIT_SUCCESS;
}