#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include <Arduino.h>
#include <co2_thresholds.h>
#include <led_indication.h>
#include <description_text.h>

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
        LEDIndication::Pattern led_indicator;
        ///< Represents the state of LED indicators used to display air quality levels.
        String description;
        ///< A string that provides a description of the air quality level.
        bool is_level_acceptable;
        ///< indicating whether the air quality level is considered acceptable (true) or not (false).
        int upper_threshold_ppm;
        ///< Specifies the upper CO2 threshold (in parts per million) for this air quality level. A value of -1
        ///< indicates no upper limit, typically representing the poorest air quality.
    };

    const Level HIGH_QUALITY = {
        LEDIndication::HIGH_QUALITY,
        DescriptionText::HIGH_QUALITY,
        true,
        CO2Thresholds::HIGH_QUALITY_PPM
    };

    const Level MEDIUM_QUALITY = {
        LEDIndication::MEDIUM_QUALITY,
        DescriptionText::MEDIUM_QUALITY,
        true,
        CO2Thresholds::MEDIUM_QUALITY_PPM
    };

    const Level LOWER_MODERATE_QUALITY = {
        LEDIndication::LOWER_MODERATE_QUALITY,
        DescriptionText::MODERATE_QUALITY,
        true,
        CO2Thresholds::LOWER_MODERATE_QUALITY_PPM
    };

    const Level UPPER_MODERATE_QUALITY = {
        LEDIndication::UPPER_MODERATE_QUALITY,
        DescriptionText::MODERATE_QUALITY,
        true,
        CO2Thresholds::UPPER_MODERATE_QUALITY_PPM
    };

    const Level POOR_QUALITY = {
        LEDIndication::POOR_QUALITY,
        DescriptionText::POOR_QUALITY,
        false,
        CO2Thresholds::NO_UPPER_LIMIT // No upper limit for poor air quality.
    };

    const Level AIR_QUALITY_LEVELS[] = {
        HIGH_QUALITY,
        MEDIUM_QUALITY,
        LOWER_MODERATE_QUALITY,
        UPPER_MODERATE_QUALITY,
        POOR_QUALITY
    };
}

#endif //AIR_QUALITY_H
