#include <Arduino.h>
#include <measurement_interpreter.h>
#include <air_quality.h>


namespace MeasurementInterpreter {
    AirQuality::Level get_air_quality_level(const int co2_measurement_ppm) {
        for (const AirQuality::Level &air_quality_level: AirQuality::AIR_QUALITY_LEVELS) {
            if (co2_measurement_ppm <= air_quality_level.upper_threshold_ppm) {
                return air_quality_level;
            }
        }
        return AirQuality::POOR_QUALITY;
    }
}
