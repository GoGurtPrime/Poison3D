#include "system_manager.h"

static short update_system_count = 0;
static short render_system_count = 0;
static system_update_callback update_system_callbacks[64] = {};
static system_update_callback render_system_callbacks[64] = {};

void systemmgr_register_system(system_update_callback cb, SystemType sys_type)
{
    if (sys_type == SYS_UPDATE)
    {
        if (update_system_count < 64)
        {
            update_system_callbacks[update_system_count] = cb;
            update_system_count++;
        }
    }
    else
    {
        if (render_system_count < 64)
        {
            render_system_callbacks[render_system_count] = cb;
            render_system_count++;
        }
    }
}

void systemmgr_exec_callbacks(float dt, SystemType sys_type)
{
    if (sys_type == SYS_UPDATE && update_system_count > 0)
    {
        for (int i = 0; i < update_system_count; i++)
        {
            update_system_callbacks[i](dt);
        }
    }
    else if (render_system_count > 0)
    {
        for (int i = 0; i < render_system_count; i++)
        {
            render_system_callbacks[i](dt);
        }
    }
}
