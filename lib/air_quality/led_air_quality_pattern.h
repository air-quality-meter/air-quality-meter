#ifndef LED_AIR_QUALITY_PATTERN_H
#define LED_AIR_QUALITY_PATTERN_H

#include <led_array.h>
namespace LEDIndication {

    constexpr LedArray::Pattern HIGH_QUALITY = {true, true, false, false, false, false};
    ///< LED indicator state for high air quality (both green LEDs ON).

    constexpr LedArray::Pattern MEDIUM_QUALITY = {false, true, true, false, false, false};
    ///< LED indicator state for medium air quality (one green and one yellow LED ON).

    constexpr LedArray::Pattern LOWER_MODERATE_QUALITY = {false, false, true, true, false, false};
    ///< LED indicator state for lower part of moderate air quality (both yellow LEDs ON).

    constexpr LedArray::Pattern UPPER_MODERATE_QUALITY = {false, false, false, true, true, false};
    ///< LED indicator state for upper part of moderate air quality (one yellow and one red LED ON).

    constexpr LedArray::Pattern POOR_QUALITY = {false, false, false, false, true, true};
    ///< LED indicator state for poor air quality (both red LEDs ON).
}
#endif //LED_AIR_QUALITY_PATTERN_H
