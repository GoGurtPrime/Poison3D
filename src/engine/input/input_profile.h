#pragma once

typedef enum {
    PC = 0,
    NINTENDO_64 = 1,
    SEGA_DREAMCAST = 2
} InputPlatform;

typedef enum {
    N64_A = 10,
    N64_B = 11,
    N64_C_UP = 12,
    N64_C_RIGHT = 13,
    N64_C_DOWN = 14,
    N64_C_LEFT = 15,
    N64_R_TRIGGER = 16,
    N64_L_TRIGGER = 17,
    N64_Z_TRIGGER = 18,
    N64_DPAD_UP = 19,
    N64_DPAD_RIGHT = 20,
    N64_DPAD_DOWN = 21,
    N64_DPAD_LEFT = 22,
    N64_JOYSTICK_X = 23,
    N64_JOYSTICK_Y = 24,
    N64_START = 25,
    
    DC_START = 26,
    DC_A = 30,
    DC_B = 31,
    DC_X = 32,
    DC_Y = 33,
    DC_R_TRIGGER = 34,
    DC_L_TRIGGER = 35,
    DC_DPAD_UP = 36,
    DC_DPAD_RIGHT = 37,
    DC_DPAD_DOWN = 38,
    DC_DPAD_LEFT = 39,
    DC_JOYSTICK_X = 40,
    DC_JOYSTICK_Y = 41,
    
    KEY_A = 42,
    KEY_B = 43,
    KEY_C = 44,
    KEY_D = 45,
    KEY_E = 46,
    KEY_F = 47,
    KEY_G = 48,
    KEY_H = 49,
    KEY_I = 50,
    KEY_J = 51,
    KEY_K = 52,
    KEY_L = 53,
    KEY_M = 54,
    KEY_N = 55,
    KEY_O = 56,
    KEY_P = 57,
    KEY_Q = 58,
    KEY_R = 59,
    KEY_S = 60,
    KEY_T = 61,
    KEY_U = 62,
    KEY_V = 63,
    KEY_W = 64,
    KEY_X = 65,
    KEY_Y = 66,
    KEY_Z = 67,
    
    KEY_0 = 68,
    KEY_1 = 69,
    KEY_2 = 70,
    KEY_3 = 71,
    KEY_4 = 72,
    KEY_5 = 73,
    KEY_6 = 74,
    KEY_7 = 75,
    KEY_8 = 76,
    KEY_9 = 77,

    KEY_SPACE = 78,
    KEY_ENTER = 79,
    KEY_ESC = 80,
    KEY_TAB = 81,
    KEY_TILDE = 82,
    KEY_GRAVE_ACCENT = 83,

    KEY_CTRL = 84,
    KEY_CTRL_LEFT = 85,
    KEY_CTRL_RIGHT = 86,
    
    KEY_ALT = 87,
    KEY_ALT_LEFT = 88,
    KEY_ALT_RIGHT = 89,

    KEY_SHIFT = 90,
    KEY_SHIFT_LEFT = 91,
    KEY_SHIFT_RIGHT = 92,

    MOUSE_X = 93,
    MOUSE_Y = 94,
    MOUSE_CLICK_LEFT = 95,
    MOUSE_CLICK_MIDDLE = 96,
    MOUSE_CLICK_RIGHT = 97
} InputCode;

typedef struct {
    InputPlatform platform;
    InputCode code;
} InputListener;

typedef struct {
    const char* action_name;
    const InputListener* listeners;
    int num_listeners;
} InputAction;

typedef struct {
    const char* map_name;
    const InputAction* actions;
    int num_actions;
} InputActionMap;

typedef struct {
    const InputActionMap* maps;
    int num_maps;
} GameInputProfile;

GameInputProfile get_input_profile();
