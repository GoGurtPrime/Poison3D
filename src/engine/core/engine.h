#pragma once
#include <stdint.h>

typedef struct EngineConfig {
    int width;
    int height;
} EngineConfig;

void engine_init(const EngineConfig* cfg);
void engine_update(float dt);
void engine_render(void);
void engine_shutdown(void);
