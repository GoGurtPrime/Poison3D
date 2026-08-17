#pragma once

typedef void (*system_update_callback)();

void system_register(system_update_callback cb);

void system_update_all();
