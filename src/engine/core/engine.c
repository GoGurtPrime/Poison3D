#include "engine.h"
#include "../renderers/renderer.h"

static EngineConfig g_cfg;

void engine_init(const EngineConfig* cfg) 
{
    g_cfg = *cfg;
    
    renderer_init(g_cfg.width, g_cfg.height);
}

void engine_update(float dt) 
{
    //(void)dt;
    // TODO: Update game state
}

void engine_render(void) 
{
    renderer_render();
}

void engine_shutdown(void)
{
    renderer_shutdown();
}
