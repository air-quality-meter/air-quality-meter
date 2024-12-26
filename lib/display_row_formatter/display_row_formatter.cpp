#include <Arduino.h>
#include <display_row_formatter.h>

const String CO2_PREFIX = "CO2: "; ///< Prefix to display CO2 value
const String PPM_SUFFIX = " ppm"; ///< Suffix to display a value with ppm as the unit

namespace DisplayRowFormatter {
    String get_co2_display_row(const int co2_measurement_ppm) {
        const String co2_display_row = CO2_PREFIX + co2_measurement_ppm + PPM_SUFFIX;
        return co2_display_row;
    }
}