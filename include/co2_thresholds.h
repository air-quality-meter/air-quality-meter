/**
   * @file co2_thresholds.h
   * @brief Constants for indoor CO2 thresholds based on air quality standards.
   *
   * @details These constants define upper limits for various air quality levels, following
   * DIN EN 13779 standards. Ranges are categorized into high, medium, moderate, and poor air quality.
   */

#ifndef CO2_THRESHOLDS_H
#define CO2_THRESHOLDS_H
namespace CO2Thresholds {
    constexpr int HIGH_QUALITY_PPM = 800;
    ///< Upper CO2 threshold (less than or equal to) for high indoor air quality (IDA 1 DIN EN 13779)
    ///< in parts per million (ppm)

    constexpr int MEDIUM_QUALITY_PPM = 1000;
    ///< Upper CO2 threshold (less than or equal to) for medium indoor air quality (IDA 2 DIN EN 13779)
    ///< in parts per million (ppm)

    constexpr int LOWER_MODERATE_QUALITY_PPM = 1200;
    ///< Upper CO2 threshold (less than or equal to) for lower half (mid) of moderate indoor air quality
    ///< (IDA 3 DIN EN 13779) parts per million (ppm). The IDA 3 bandwidth is double the size of the IDA 2 bandwidth,
    ///< which is why it is divided into two halves here.

    constexpr int UPPER_MODERATE_QUALITY_PPM = 1400;
    ///< Upper CO2 threshold (less than or equal to) for moderate indoor air quality (IDA 3 DIN EN 13779)
    ///< parts per million (ppm). At the same time, this value represents the lower threshold (greater than) value
    ///< for poor indoor air quality (IDA 4 DIN EN 13779)

    constexpr int NO_UPPER_LIMIT = -1;
    ///< Indicates that there is no upper limit for a given air quality level.
}
#endif //CO2_THRESHOLDS_H
