#pragma once

typedef void (*system_update_callback)();

typedef enum {
    SYS_UPDATE,
    SYS_RENDER
} SystemType;

void systemmgr_register_system(system_update_callback cb, SystemType sys_type);

void systemmgr_update_all();
