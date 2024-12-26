#ifndef LED_AIR_QUALITY_PATTERN_H
#define LED_AIR_QUALITY_PATTERN_H

#include <led_pattern.h>

namespace LEDIndication {

    constexpr LedPattern::Pattern HIGH_QUALITY = {true, true, false, false, false, false};
    ///< LED indicator state for high air quality (both green LEDs ON).

    constexpr LedPattern::Pattern MEDIUM_QUALITY = {false, true, true, false, false, false};
    ///< LED indicator state for medium air quality (one green and one yellow LED ON).

    constexpr LedPattern::Pattern LOWER_MODERATE_QUALITY = {false, false, true, true, false, false};
    ///< LED indicator state for lower part of moderate air quality (both yellow LEDs ON).

    constexpr LedPattern::Pattern UPPER_MODERATE_QUALITY = {false, false, false, true, true, false};
    ///< LED indicator state for upper part of moderate air quality (one yellow and one red LED ON).

    constexpr LedPattern::Pattern POOR_QUALITY = {false, false, false, false, true, true};
    ///< LED indicator state for poor air quality (both red LEDs ON).
}
#endif //LED_AIR_QUALITY_PATTERN_H
