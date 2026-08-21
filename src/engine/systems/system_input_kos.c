#include "system_input.h"
#include <kos.h>
#include <string.h>

#define MAX_ACTIVE_ACTIONS 64

static GameInputProfile input_profile;
static ActionValue active_actions[MAX_ACTIVE_ACTIONS];
static int num_active_actions = 0;

// Helper to convert Dreamcast hardware state to a 0.0 - 1.0 float
static float read_dc_input(InputCode code)
{
    // Grab the first controller found on the Maple bus (usually Port A)
    maple_device_t *cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
    
    // If no controller is plugged in, return 0 for all inputs
    if (!cont) return 0.0f;

    cont_state_t *state = (cont_state_t *)maple_dev_status(cont);
    if (!state) return 0.0f;

    switch (code) {
        // --- Face Buttons ---
        case DC_START: return (state->buttons & CONT_START) ? 1.0f : 0.0f;
        case DC_A:     return (state->buttons & CONT_A) ? 1.0f : 0.0f;
        case DC_B:     return (state->buttons & CONT_B) ? 1.0f : 0.0f;
        case DC_X:     return (state->buttons & CONT_X) ? 1.0f : 0.0f;
        case DC_Y:     return (state->buttons & CONT_Y) ? 1.0f : 0.0f;

        // --- D-Pad ---
        case DC_DPAD_UP:    return (state->buttons & CONT_DPAD_UP) ? 1.0f : 0.0f;
        case DC_DPAD_DOWN:  return (state->buttons & CONT_DPAD_DOWN) ? 1.0f : 0.0f;
        case DC_DPAD_LEFT:  return (state->buttons & CONT_DPAD_LEFT) ? 1.0f : 0.0f;
        case DC_DPAD_RIGHT: return (state->buttons & CONT_DPAD_RIGHT) ? 1.0f : 0.0f;

        // --- Analog Triggers (0 to 255) ---
        case DC_L_TRIGGER:  return (float)state->ltrig / 255.0f;
        case DC_R_TRIGGER:  return (float)state->rtrig / 255.0f;

        // --- Analog Stick (-128 to 127) ---
        // Normalizing positive values to 0.0 - 1.0
        case DC_JOYSTICK_X: 
            if (state->joyx > 0) return (float)state->joyx / 127.0f;
            return 0.0f;
        case DC_JOYSTICK_Y:
            if (state->joyy > 0) return (float)state->joyy / 127.0f;
            return 0.0f;

        default: return 0.0f;
    }
}

void set_action_map(const char* action_map_name)
{
    num_active_actions = 0; 
    
    for (int i = 0; i < input_profile.num_maps; i++)
    {
        if (strcmp(input_profile.maps[i].map_name, action_map_name) == 0)
        {
            const InputActionMap* map = &input_profile.maps[i];
            
            for (int j = 0; j < map->num_actions && num_active_actions < MAX_ACTIVE_ACTIONS; j++)
            {
                const InputAction* action = &map->actions[j];
                
                // Find the Dreamcast listener for this action
                for (int k = 0; k < action->num_listeners; k++)
                {
                    if (action->listeners[k].platform == SEGA_DREAMCAST)
                    {
                        active_actions[num_active_actions].action_name = action->action_name;
                        active_actions[num_active_actions].code = action->listeners[k].code;
                        active_actions[num_active_actions].current_value = 0.0f;
                        num_active_actions++;
                        
                        break; 
                    }
                }
            }
            break; 
        }
    }
}

void system_input_init()
{
    input_profile = get_input_profile();

    if (input_profile.num_maps > 0) {
        set_action_map(input_profile.maps[0].map_name);
    }
}

void system_input_update(float dt)
{
    // KOS updates maple devices in the background via hardware interrupts (vblank).
    // We don't need to manually pump events like SDL; we just read the latest state.

    for (int i = 0; i < num_active_actions; i++)
    {
        active_actions[i].current_value = read_dc_input(active_actions[i].code);
    }
}

ActionValue* get_action_value(const char* action_name)
{
    for (int i = 0; i < num_active_actions; i++)
    {
        if (strcmp(active_actions[i].action_name, action_name) == 0)
        {
            return &active_actions[i];
        }
    }
    
    return NULL; 
}