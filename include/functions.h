#include "esphome/core/component.h"
#include "esphome/components/cover/cover.h"
#include "esphome/components/output/binary_output.h"


void cover_open_or_stop(Cover *cover) {
    if (cover->current_operation == cover::COVER_OPERATION_OPENING) {
        cover->make_call().set_command_stop().perform();
        return;
    }
    cover->make_call().set_command_open().perform();
}

void cover_close_or_stop(Cover *cover) {
    if (cover->current_operation == cover::COVER_OPERATION_CLOSING) {
        cover->make_call().set_command_stop().perform();
        return;
    }
    cover->make_call().set_command_close().perform();
}

bool is_any_light_on(LightState *light) {
    return light->remote_values.is_on();
}

template<typename... Args>
bool is_any_light_on(LightState *light, Args... args) {
    return light->remote_values.is_on() || is_any_light_on(args...);
}

void light_turn_on(LightState *light) {
    light->turn_on().perform();
}

/**
 * Turn on multiple lights.
 *
 * Example:
 * @code{.cpp}
 * - platform: gpio
 *   name: "Input 7/7 Kitchet Button"
 *   pin:
 *     sn74hc165: inputs
 *     number: 46
 *     inverted: true
 *     mode:
 *       input: true
 *   on_press:
 *     then:
 *       - lambda: |-
 *           light_turn_on(kitchen_stove_light, kitchen_ceiling_light, kitchen_counter_light);
 * @endcode
 */
template<typename... Args>
void light_turn_on(LightState *light, Args... args) {
    light->turn_on().perform();
    light_turn_on(args...);
}

void light_turn_off(LightState *light) {
    light->turn_off().perform();
}

/**
 * Turn off multiple lights.
 *
 * Example:
 * @code{.cpp}
 * - platform: gpio
 *   name: "Input 7/7 Kitchet Button"
 *   pin:
 *     sn74hc165: inputs
 *     number: 46
 *     inverted: true
 *     mode:
 *       input: true
 *   on_press:
 *     then:
 *       - lambda: |-
 *           light_turn_off(kitchen_stove_light, kitchen_ceiling_light, kitchen_counter_light);
 * @endcode
 */
template<typename... Args>
void light_turn_off(LightState *light, Args... args) {
    light->turn_off().perform();
    light_turn_off(args...);
}

/**
 * Toggle multiple lights.
 *
 * If any light is on, turn all off. Otherwise, turn all on.
 * Example:
 *
 * @code{.cpp}
 * - platform: gpio
 *   name: "Input 7/7 Kitchet Button"
 *   pin:
 *     sn74hc165: inputs
 *     number: 46
 *     inverted: true
 *     mode:
 *       input: true
 *   on_press:
 *     then:
 *       - lambda: |-
 *           light_toggle(kitchen_stove_light, kitchen_ceiling_light, kitchen_counter_light);
 * @endcode
 */
template<typename... Args>
void light_toggle(LightState *light, Args... args) {
    if (is_any_light_on(light, args...)) {
        light_turn_off(light, args ...);
    } else {
        light_turn_on(light, args ...);
    }
}

/**
 * Set binary output on when any of the given lights are on, off otherwise.
 *
 * Example:
 * @code{.cpp}
 * light:
 * - platform: binary
 *   id: kitchen
 *   name: "corridor"
 *   output: out_port1_pin0
 *   restore_mode: RESTORE_DEFAULT_OFF
 *   on_state:
 *     then:
 *       - lambda: |-
 *           output_on_when_any_light_on(kitchen, toilet);
 */
template<typename... Args>
void output_on_when_any_light_on(BinaryOutput *output, LightState *light, Args... args) {
    if (is_any_light_on(light, args...)) {
        output->turn_on();
    } else {
        output->turn_off();
    }
}
