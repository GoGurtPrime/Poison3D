#include "system_manager.h"

static short system_count = 1;
static system_update_callback system_callbacks[64] = {};

void system_register(system_update_callback cb)
{
    if (system_count < 64)
    {
        system_callbacks[system_count - 1] = cb;
    }
}

void system_update_all()
{
    for (int i = 0; i < system_count; i++)
    {
        system_callbacks[i]();
    }
}
