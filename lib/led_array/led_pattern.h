#ifndef LED_PATTERN_H
#define LED_PATTERN_H
namespace LedPattern {
    /**
     * @struct  Pattern
     * @brief   Represents the state of LED indicators used to display air quality levels.
     *
     * @details This structure defines six boolean flags corresponding to the on/off state of different LEDs.
     *          Multiple LEDs can be turned on simultaneously.
     */
    struct Pattern {
        bool is_green_led_1_on; ///< Indicates if the first green LED is ON (true) or OFF (false).
        bool is_green_led_2_on; ///< Indicates if the second green LED is ON (true) or OFF (false).
        bool is_yellow_led_1_on; ///< Indicates if the first yellow LED is ON (true) or OFF (false).
        bool is_yellow_led_2_on; ///< Indicates if the second yellow LED is ON (true) or OFF (false).
        bool is_red_led_1_on; ///< Indicates if the first red LED is ON (true) or OFF (false).
        bool is_red_led_2_on; ///< Indicates if the second red LED is ON (true) or OFF (false).
    };
}
#endif //LED_PATTERN_H
