#include "system_camera_ctrl.h"
#include "system_input.h"
#include "../core/scene.h"
#include <math.h>

static ActionValue *joystick_x;
static ActionValue *joystick_y;
static scene_t *scene;

// Store the current turning speed to calculate inertia
static float current_yaw_velocity = 0.0f;

void system_camera_ctrl_init()
{
    scene = get_scene();
    joystick_x = get_action_value("JoystickX");
    joystick_y = get_action_value("JoystickY");
}

/// @brief Perform logic for the system
/// @param dt delta time in milliseconds since last frame
void system_camera_ctrl_update(float dt)
{
    float dt_sec = dt;

    float normalized_input = (joystick_x->current_value - 0.5f) * 2.0f; 

    float max_speed = 120.0f; 
    float target_velocity = normalized_input * max_speed;

    // The smoothing factor dictates how fast the camera catches up to the joystick.
    // Lower number = more slide/inertia. Higher number = snappier.
    float smoothing_factor = 10.0f; 
    current_yaw_velocity += (target_velocity - current_yaw_velocity) * (smoothing_factor * dt_sec);

    // Apply the smoothed velocity to the Y-axis rotation (rotation[1])
    scene->camera_transform->rotation[1] += current_yaw_velocity * dt_sec;

    // Wrap the rotation safely within 0 to 360 degrees
    scene->camera_transform->rotation[1] = fmodf(scene->camera_transform->rotation[1], 360.0f);
    
    // fmodf can return negative numbers if we rotated below 0, so we push it back around to 360
    if (scene->camera_transform->rotation[1] < 0.0f)
    {
        scene->camera_transform->rotation[1] += 360.0f;
    }
}