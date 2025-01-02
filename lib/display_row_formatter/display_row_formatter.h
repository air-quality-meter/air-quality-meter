/**
 * @file display_row_formatter.h
 * @brief Provides declarations for formatting rows to display CO2 values.
 */

#ifndef DISPLAY_ROW_FORMATTER_H
#define DISPLAY_ROW_FORMATTER_H

namespace DisplayRowFormatter {
    constexpr char CO2_PREFIX[] = "CO2: "; ///< Prefix for displaying CO2 measurement values.
    constexpr char PPM_SUFFIX[] = " ppm"; ///< Suffix for displaying values in ppm (parts per million).
    constexpr size_t C02_PREFIX_LENGTH = sizeof(CO2_PREFIX) - 1;
    ///< Length of the CO2 prefix (excluding the null terminator).
    constexpr size_t PPM_SUFFIX_LENGTH = sizeof(PPM_SUFFIX) - 1;
    ///< Length of the ppm suffix (excluding the null terminator).
    constexpr size_t MAX_DIGITS_IN_CO2_VALUE = 5;
    ///< Maximum number of digits expected in CO2 ppm values (supports 0–99999).
    constexpr size_t BUFFER_SIZE = C02_PREFIX_LENGTH + MAX_DIGITS_IN_CO2_VALUE + PPM_SUFFIX_LENGTH + 1;
    ///< Required size for a character buffer to store formatted CO2 output (including null terminator).

    /**
     * @brief Formats a display row with the given CO2 measurement in ppm.
     *
     * @details This function takes a buffer and formats a display string
     *          including the CO2 measurement value with appropriate
     *          prefixes, suffixes, and units (ppm). It checks for invalid input,
     *          such as a null pointer for the buffer, and performs no operations
     *          in such cases.
     *
     * @param buffer A pointer to a character array where the formatted string
     *               will be stored.
     *
     * @param co2_measurement_ppm The CO2 measurement in parts per million (ppm).
     */
    void set_co2_display_row(char *buffer, int co2_measurement_ppm);
}
#endif //DISPLAY_ROW_FORMATTER_H
