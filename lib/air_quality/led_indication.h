#ifndef LED_INDICATION_H
#define LED_INDICATION_H
namespace LEDIndication {
    /**
     * @struct  Pattern
     * @brief   Represents the state of LED indicators used to display air quality levels.
     *
     * @details This structure defines six boolean flags corresponding to the on/off state of different LEDs.
     *          Multiple LEDs can be turned on simultaneously to indicate an air quality status.
     */
    struct Pattern {
        bool is_green_led_1_on; ///< Indicates if the first green LED is ON (true) or OFF (false).
        bool is_green_led_2_on; ///< Indicates if the second green LED is ON (true) or OFF (false).
        bool is_yellow_led_1_on; ///< Indicates if the first yellow LED is ON (true) or OFF (false).
        bool is_yellow_led_2_on; ///< Indicates if the second yellow LED is ON (true) or OFF (false).
        bool is_red_led_1_on; ///< Indicates if the first red LED is ON (true) or OFF (false).
        bool is_red_led_2_on; ///< Indicates if the second red LED is ON (true) or OFF (false).
    };

    constexpr Pattern HIGH_QUALITY = {true, true, false, false, false, false};
    ///< LED indicator state for high air quality (both green LEDs ON).

    constexpr Pattern MEDIUM_QUALITY = {false, true, true, false, false, false};
    ///< LED indicator state for medium air quality (one green and one yellow LED ON).

    constexpr Pattern LOWER_MODERATE_QUALITY = {false, false, true, true, false, false};
    ///< LED indicator state for lower part of moderate air quality (both yellow LEDs ON).

    constexpr Pattern UPPER_MODERATE_QUALITY = {false, false, false, true, true, false};
    ///< LED indicator state for upper part of moderate air quality (one yellow and one red LED ON).

    constexpr Pattern POOR_QUALITY = {false, false, false, false, true, true};
    ///< LED indicator state for poor air quality (both red LEDs ON).
}
#endif //LED_INDICATION_H
