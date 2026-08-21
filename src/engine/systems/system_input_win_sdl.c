#include "system_input.h"
#include <SDL.h>
#include <string.h>

#define MAX_ACTIVE_ACTIONS 64

static GameInputProfile input_profile;
static ActionValue active_actions[MAX_ACTIVE_ACTIONS];
static int num_active_actions = 0;

// Helper to convert SDL hardware state to a 0.0 - 1.0 float
static float read_pc_input(InputCode code)
{
    // SDL gives us a pointer to the entire keyboard state array.
    // This is updated internally whenever SDL_PumpEvents() is called in your main loop.
    const Uint8* state = SDL_GetKeyboardState(NULL);

    switch (code) {
        // --- Letters ---
        case KEY_A: return state[SDL_SCANCODE_A] ? 1.0f : 0.0f;
        case KEY_B: return state[SDL_SCANCODE_B] ? 1.0f : 0.0f;
        case KEY_C: return state[SDL_SCANCODE_C] ? 1.0f : 0.0f;
        case KEY_D: return state[SDL_SCANCODE_D] ? 1.0f : 0.0f;
        case KEY_E: return state[SDL_SCANCODE_E] ? 1.0f : 0.0f;
        case KEY_F: return state[SDL_SCANCODE_F] ? 1.0f : 0.0f;
        case KEY_G: return state[SDL_SCANCODE_G] ? 1.0f : 0.0f;
        case KEY_H: return state[SDL_SCANCODE_H] ? 1.0f : 0.0f;
        case KEY_I: return state[SDL_SCANCODE_I] ? 1.0f : 0.0f;
        case KEY_J: return state[SDL_SCANCODE_J] ? 1.0f : 0.0f;
        case KEY_K: return state[SDL_SCANCODE_K] ? 1.0f : 0.0f;
        case KEY_L: return state[SDL_SCANCODE_L] ? 1.0f : 0.0f;
        case KEY_M: return state[SDL_SCANCODE_M] ? 1.0f : 0.0f;
        case KEY_N: return state[SDL_SCANCODE_N] ? 1.0f : 0.0f;
        case KEY_O: return state[SDL_SCANCODE_O] ? 1.0f : 0.0f;
        case KEY_P: return state[SDL_SCANCODE_P] ? 1.0f : 0.0f;
        case KEY_Q: return state[SDL_SCANCODE_Q] ? 1.0f : 0.0f;
        case KEY_R: return state[SDL_SCANCODE_R] ? 1.0f : 0.0f;
        case KEY_S: return state[SDL_SCANCODE_S] ? 1.0f : 0.0f;
        case KEY_T: return state[SDL_SCANCODE_T] ? 1.0f : 0.0f;
        case KEY_U: return state[SDL_SCANCODE_U] ? 1.0f : 0.0f;
        case KEY_V: return state[SDL_SCANCODE_V] ? 1.0f : 0.0f;
        case KEY_W: return state[SDL_SCANCODE_W] ? 1.0f : 0.0f;
        case KEY_X: return state[SDL_SCANCODE_X] ? 1.0f : 0.0f;
        case KEY_Y: return state[SDL_SCANCODE_Y] ? 1.0f : 0.0f;
        case KEY_Z: return state[SDL_SCANCODE_Z] ? 1.0f : 0.0f;

        // --- Numbers ---
        case KEY_0: return state[SDL_SCANCODE_0] ? 1.0f : 0.0f;
        case KEY_1: return state[SDL_SCANCODE_1] ? 1.0f : 0.0f;
        case KEY_2: return state[SDL_SCANCODE_2] ? 1.0f : 0.0f;
        case KEY_3: return state[SDL_SCANCODE_3] ? 1.0f : 0.0f;
        case KEY_4: return state[SDL_SCANCODE_4] ? 1.0f : 0.0f;
        case KEY_5: return state[SDL_SCANCODE_5] ? 1.0f : 0.0f;
        case KEY_6: return state[SDL_SCANCODE_6] ? 1.0f : 0.0f;
        case KEY_7: return state[SDL_SCANCODE_7] ? 1.0f : 0.0f;
        case KEY_8: return state[SDL_SCANCODE_8] ? 1.0f : 0.0f;
        case KEY_9: return state[SDL_SCANCODE_9] ? 1.0f : 0.0f;

        // --- Specials ---
        case KEY_SPACE:        return state[SDL_SCANCODE_SPACE] ? 1.0f : 0.0f;
        case KEY_ENTER:        return state[SDL_SCANCODE_RETURN] ? 1.0f : 0.0f;
        case KEY_ESC:          
            return state[SDL_SCANCODE_ESCAPE] ? 1.0f : 0.0f;
        case KEY_TAB:          return state[SDL_SCANCODE_TAB] ? 1.0f : 0.0f;
        case KEY_TILDE:        return state[SDL_SCANCODE_GRAVE] ? 1.0f : 0.0f;
        case KEY_GRAVE_ACCENT: return state[SDL_SCANCODE_GRAVE] ? 1.0f : 0.0f;

        // --- Modifiers ---
        case KEY_CTRL:       return (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) ? 1.0f : 0.0f;
        case KEY_CTRL_LEFT:  return state[SDL_SCANCODE_LCTRL] ? 1.0f : 0.0f;
        case KEY_CTRL_RIGHT: return state[SDL_SCANCODE_RCTRL] ? 1.0f : 0.0f;
        
        case KEY_ALT:       return (state[SDL_SCANCODE_LALT] || state[SDL_SCANCODE_RALT]) ? 1.0f : 0.0f;
        case KEY_ALT_LEFT:  return state[SDL_SCANCODE_LALT] ? 1.0f : 0.0f;
        case KEY_ALT_RIGHT: return state[SDL_SCANCODE_RALT] ? 1.0f : 0.0f;

        case KEY_SHIFT:       return (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) ? 1.0f : 0.0f;
        case KEY_SHIFT_LEFT:  return state[SDL_SCANCODE_LSHIFT] ? 1.0f : 0.0f;
        case KEY_SHIFT_RIGHT: return state[SDL_SCANCODE_RSHIFT] ? 1.0f : 0.0f;

        // --- Mouse ---
        case MOUSE_X: {
            int mx, my;
            // GetRelativeMouseState is usually preferred for game cameras/aiming
            // It returns the delta since the last time it was checked.
            SDL_GetRelativeMouseState(&mx, &my);
            
            // NOTE: This breaks the 0.0 - 1.0 rule! Mouse delta can be negative or > 1.0. 
            // You may need to normalize this against your screen width or a sensitivity constant.
            return (float)mx; 
        }
        case MOUSE_Y: {
            int mx, my;
            SDL_GetRelativeMouseState(&mx, &my);
            return (float)my;
        }

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
                
                // Find the PC listener for this action
                for (int k = 0; k < action->num_listeners; k++)
                {
                    if (action->listeners[k].platform == PC)
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
    // SDL_PumpEvents() updates the keyboard and mouse states.
    // If you already call SDL_PollEvent() in your main Windows loop, you 
    // technically don't need this, but it's safe to call here to guarantee fresh data.
    SDL_PumpEvents();

    for (int i = 0; i < num_active_actions; i++)
    {
        active_actions[i].current_value = read_pc_input(active_actions[i].code);

        if (active_actions[i].current_value == 1.0f)
        {
            printf("Hit!");
        }
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