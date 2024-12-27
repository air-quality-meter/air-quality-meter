#ifndef DISPLAY_ROW_FORMATTER_H
#define DISPLAY_ROW_FORMATTER_H

#include <Arduino.h>

namespace DisplayRowFormatter {
    /**
     * @brief   Updates the display with the air quality measurement and description.
     *
     * @details This function formats and combines CO2 measurement in ppm and its corresponding air
     *          quality description. It then outputs the results to the display device.
     *
     * @param co2_measurement_ppm The CO2 measurement in parts per million (ppm).
     */
    String get_co2_display_row(int co2_measurement_ppm);
}
#endif //DISPLAY_ROW_FORMATTER_H
