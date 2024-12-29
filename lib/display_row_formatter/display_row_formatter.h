#ifndef DISPLAY_ROW_FORMATTER_H
#define DISPLAY_ROW_FORMATTER_H

namespace DisplayRowFormatter {
    constexpr char CO2_PREFIX[] = "CO2: "; ///< Prefix to display CO2 value
    constexpr char PPM_SUFFIX[] = " ppm"; ///< Suffix to display a value with ppm as the unit
    constexpr size_t C02_PREFIX_LENGTH = sizeof(CO2_PREFIX) - 1;
    ///< Length of the co2 prefix (subtract null terminator)
    constexpr size_t PPM_SUFFIX_LENGTH = sizeof(PPM_SUFFIX) - 1;
    ///< Length of the ppm suffix (subtract null terminator)
    constexpr size_t MAX_DIGITS_IN_CO2_VALUE = 5;
    ///< Maximum number of digits in a CO2 value (0 - 10000)
    constexpr size_t BUFFER_SIZE = C02_PREFIX_LENGTH + MAX_DIGITS_IN_CO2_VALUE + PPM_SUFFIX_LENGTH + 1;
    ///< Size of the buffer (including null terminator)

    /**
     * @brief   Updates the display with the air quality measurement and description.
     *
     * @details This function formats and combines CO2 measurement in ppm and its corresponding air
     *          quality description. It then outputs the results to the display device.
     *
     * @param buffer
     * @param co2_measurement_ppm The CO2 measurement in parts per million (ppm).
     */
    void set_co2_display_row(char *buffer, int co2_measurement_ppm);
}
#endif //DISPLAY_ROW_FORMATTER_H
