#include <Arduino.h>
#include <measurement_interpreter.h>
#include <air_quality_level.h>


AirQualityLevel::AirQualityLevel get_air_quality_level(const int co2_measurement_ppm) {
    for (const AirQualityLevel::AirQualityLevel &air_quality_level: AirQualityLevel::AIR_QUALITY_LEVELS) {
        if (co2_measurement_ppm <= air_quality_level.upper_threshold_ppm) {
            return air_quality_level;
        }
    }
    return AirQualityLevel::POOR_AIR_QUALITY_LEVEL;
}
