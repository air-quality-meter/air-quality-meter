#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include <co2_thresholds.h>
#include <description_text.h>
#include <led_patterns.h>

namespace AirQuality {
    /**
     * @struct  Level
     * @brief   Represents the characteristics and thresholds for a specific air quality level.
     *
     * @details This structure defines a mapping between air quality levels and their associated attributes.
     *          It includes thresholds for CO2 measurements, descriptive labels, LED indicator states,
     *          and an acceptability status.
     */
    struct Level {
        LedPattern::Pattern led_indicator;
        ///< Represents the state of LED indicators used to display air quality levels.
        const char *description;
        ///< A string that provides a description of the air quality level.
        bool is_acceptable;
        ///< indicating whether the air quality level is considered acceptable (true) or not (false).
        int upper_threshold_ppm;
        ///< Specifies the upper CO2 threshold (in parts per million) for this air quality level. A value of -1
        ///< indicates no upper limit, typically representing the poorest air quality.
    };

    constexpr Level HIGH_QUALITY = {
        LedAirQualityPattern::HIGH_QUALITY,
        DescriptionText::HIGH_QUALITY,
        true,
        CO2Thresholds::HIGH_QUALITY_PPM
    };

    constexpr Level MEDIUM_QUALITY = {
        LedAirQualityPattern::MEDIUM_QUALITY,
        DescriptionText::MEDIUM_QUALITY,
        true,
        CO2Thresholds::MEDIUM_QUALITY_PPM
    };

    constexpr Level LOWER_MODERATE_QUALITY = {
        LedAirQualityPattern::LOWER_MODERATE_QUALITY,
        DescriptionText::MODERATE_QUALITY,
        true,
        CO2Thresholds::LOWER_MODERATE_QUALITY_PPM
    };

    constexpr Level UPPER_MODERATE_QUALITY = {
        LedAirQualityPattern::UPPER_MODERATE_QUALITY,
        DescriptionText::MODERATE_QUALITY,
        true,
        CO2Thresholds::UPPER_MODERATE_QUALITY_PPM
    };

    constexpr Level POOR_QUALITY = {
        LedAirQualityPattern::POOR_QUALITY,
        DescriptionText::POOR_QUALITY,
        false,
        CO2Thresholds::NO_UPPER_LIMIT // No upper limit for poor air quality.
    };

    constexpr Level AIR_QUALITY_LEVELS[] = {
        HIGH_QUALITY,
        MEDIUM_QUALITY,
        LOWER_MODERATE_QUALITY,
        UPPER_MODERATE_QUALITY,
        POOR_QUALITY
    };
}

#endif //AIR_QUALITY_H
