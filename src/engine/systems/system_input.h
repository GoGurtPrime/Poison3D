#pragma once

#include "../input/input_profile.h"

typedef struct {
    const char* action_name;
    InputCode code;
    float current_value;
} ActionValue;

void system_input_init();

void system_input_update(float dt);

void set_action_map(const char* action_map_name);

ActionValue* get_action_value(const char* action_name);