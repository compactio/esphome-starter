#include "esphome/core/component.h"
#include "esphome/components/cover/cover.h"


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

boolean is_any_light_on(LightState *light) {
    return light->remote_values.is_on();
}

template<typename... Args>
boolean is_any_light_on(LightState *light, Args... args) {
    return light->remote_values.is_on() || is_any_light_on(args...);
}

void light_turn_on(LightState *light) {
    light->turn_on().perform();
}

template<typename... Args>
void light_turn_on(LightState *light, Args... args) {
    light->turn_on().perform();
    light_turn_on(args...);
}

void light_turn_off(LightState *light) {
    light->turn_off().perform();
}

template<typename... Args>
void light_turn_off(LightState *light, Args... args) {
    light->turn_off().perform();
    light_turn_off(args...);
}

template<typename... Args>
void light_toggle(LightState *light, Args... args) {
    if (is_any_light_on(light, args...)) {
        light_turn_off(light, args ...);
    } else {
        light_turn_on(light, args ...);
    }
}
