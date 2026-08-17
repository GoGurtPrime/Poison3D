#include "engine.h"
#include "system_manager.h"
#include "../renderers/renderer.h"
#include "../systems/system_input.h"

static EngineConfig g_cfg;

void engine_init(const EngineConfig* cfg) 
{
    g_cfg = *cfg;
    
    renderer_init(g_cfg.width, g_cfg.height);

    systemmgr_register_system(system_input_update, SYS_UPDATE);
}

void engine_update(float dt) 
{
    systemmgr_exec_callbacks(dt, SYS_UPDATE);
}

void engine_render(void) 
{
    systemmgr_exec_callbacks(.0f, SYS_RENDER);
    renderer_render();
}

void engine_shutdown(void)
{
    renderer_shutdown();
}
