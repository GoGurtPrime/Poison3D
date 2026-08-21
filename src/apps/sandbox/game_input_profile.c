/**
 * Defined by game code, instructs the engine on setting
 * up named listeners.
 */

#include "../../engine/input/input_profile.h"

static const InputListener reset_listeners[] = {
    { PC, KEY_ESC },
    { NINTENDO_64, N64_START },
    { SEGA_DREAMCAST, DC_START }
};

static const InputListener joystick_x[] = {
    { PC, MOUSE_X },
    { NINTENDO_64, N64_JOYSTICK_X },
    { SEGA_DREAMCAST, DC_JOYSTICK_X }
};

static const InputListener joystick_y[] = {
    { PC, MOUSE_Y },
    { NINTENDO_64, N64_JOYSTICK_Y },
    { SEGA_DREAMCAST, DC_JOYSTICK_Y }
};

static const InputAction gameplay_actions[] = {
    { "Reset", reset_listeners, sizeof(reset_listeners) / sizeof(InputListener) },
    { "JoystickX", joystick_x, sizeof(joystick_x) / sizeof(InputListener) },
    { "JoystickY", joystick_y, sizeof(joystick_y) / sizeof(InputListener) },
};

static const InputActionMap profile_maps[] = {
    { "Gameplay", gameplay_actions, sizeof(gameplay_actions) / sizeof(InputAction) }
};

static const GameInputProfile global_profile = {
    profile_maps,
    sizeof(profile_maps) / sizeof(InputActionMap)
};

GameInputProfile get_input_profile()
{
    return global_profile;
}
