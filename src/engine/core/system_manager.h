#pragma once

// dt is delta time from last frame
typedef void (*system_update_callback)(float dt);

typedef enum {
    SYS_UPDATE,
    SYS_RENDER
} SystemType;

void systemmgr_register_system(system_update_callback cb, SystemType sys_type);

void systemmgr_exec_callbacks(float dt, SystemType sys_type);
