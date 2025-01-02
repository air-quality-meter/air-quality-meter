/**
 * @file display_row_formatter.cpp
 * @brief Implementation of display row formatting for CO2 measurement values.
 */

#include <Arduino.h>
#include <display_row_formatter.h>


namespace DisplayRowFormatter {
    void set_co2_display_row(char *buffer, const int co2_measurement_ppm) {
        if (!buffer) {
            return; // no operation if buffer is null
        }
        snprintf(buffer, BUFFER_SIZE, "%s%d%s", CO2_PREFIX, co2_measurement_ppm, PPM_SUFFIX);
    }
}
