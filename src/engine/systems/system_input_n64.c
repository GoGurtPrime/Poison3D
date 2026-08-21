#include "system_input.h"
#include "joypad.h"
#include <string.h>

#define MAX_ACTIVE_ACTIONS 64

static GameInputProfile input_profile;
static ActionValue active_actions[MAX_ACTIVE_ACTIONS];
static int num_active_actions = 0;

// Helper to convert N64 hardware state to a 0.0 - 1.0 float
static float read_n64_input(InputCode code)
{
    joypad_inputs_t inputs = joypad_get_inputs(0); // Port 1
    
    switch (code) {
        case N64_A: return inputs.btn.a ? 1.0f : 0.0f;
        case N64_B: return inputs.btn.b ? 1.0f : 0.0f;
        case N64_Z_TRIGGER: return inputs.btn.z ? 1.0f : 0.0f;
        case N64_START: return inputs.btn.start ? 1.0f : 0.0f;
        
        // D-Pad
        case N64_DPAD_UP: return inputs.btn.d_up ? 1.0f : 0.0f;
        case N64_DPAD_DOWN: return inputs.btn.d_down ? 1.0f : 0.0f;
        case N64_DPAD_LEFT: return inputs.btn.d_left ? 1.0f : 0.0f;
        case N64_DPAD_RIGHT: return inputs.btn.d_right ? 1.0f : 0.0f;

        // Analog stick (N64 stick typically ranges roughly -85 to +85)
        // Normalize positive values to 0.0 - 1.0
        case N64_JOYSTICK_X: 
            if (inputs.stick_x > 0) return inputs.stick_x / 85.0f; 
            return 0.0f; 
        case N64_JOYSTICK_Y: 
            if (inputs.stick_y > 0) return inputs.stick_y / 85.0f; 
            return 0.0f;

        // Add C-Buttons, Triggers, and negative axis logic here...
        default: return 0.0f;
    }
}

void set_action_map(const char* action_map_name)
{
    num_active_actions = 0; // Clear current active actions
    
    // Find the requested map
    for (int i = 0; i < input_profile.num_maps; i++)
    {
        if (strcmp(input_profile.maps[i].map_name, action_map_name) == 0)
        {
            const InputActionMap* map = &input_profile.maps[i];
            
            // Loop through all actions in this map
            for (int j = 0; j < map->num_actions && num_active_actions < MAX_ACTIVE_ACTIONS; j++)
            {
                const InputAction* action = &map->actions[j];
                
                // Find the N64 listener for this action
                for (int k = 0; k < action->num_listeners; k++)
                {
                    if (action->listeners[k].platform == NINTENDO_64)
                    {
                        // Store it in our active array
                        active_actions[num_active_actions].action_name = action->action_name;
                        active_actions[num_active_actions].code = action->listeners[k].code;
                        active_actions[num_active_actions].current_value = 0.0f;
                        num_active_actions++;
                        
                        break; // Found N64 mapping, move to next action
                    }
                }
            }
            break; // Map found and loaded, stop searching maps
        }
    }
}

void system_input_init()
{
    input_profile = get_input_profile();

    if (input_profile.num_maps > 0) 
    {
        // Load the first map by default
        set_action_map(input_profile.maps[0].map_name);
    }
}

void system_input_update(float dt)
{
    // Update our float values
    for (int i = 0; i < num_active_actions; i++)
    {
        active_actions[i].current_value = read_n64_input(active_actions[i].code);
        
        // Optional: Clamp values here in case an old N64 stick pushes past 85
        if (active_actions[i].current_value > 1.0f) 
        {
            active_actions[i].current_value = 1.0f;
        }
    }
}

ActionValue* get_action_value(const char* action_name)
{
    // This string lookup is fine because game logic should only call it 
    // once during initialization or when the map changes.
    for (int i = 0; i < num_active_actions; i++)
    {
        if (strcmp(active_actions[i].action_name, action_name) == 0)
        {
            return &active_actions[i];
        }
    }
    
    return NULL; // Action not found in current map
}