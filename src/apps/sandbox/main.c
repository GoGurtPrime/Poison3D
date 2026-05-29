#include <stdio.h>
#include "../../platforms/platform.h"
#include "../../engine/core/engine.h"

int main(void) {
    Platform plat = {0};

    // printf("Starting platform");
    if (!platform_init(&plat, "Poison3D Sandbox", 640, 480)) 
    {
        // printf("Platform failed to load! Exit 1");

        return 1;
    }

    // printf("Platform loaded, now running engine init...");

    EngineConfig cfg = { plat.width, plat.height };
    engine_init(&cfg);

    // printf("Finished engine init...");
    // printf("Running platform loop");

    while (plat.running) {
        // printf(".");
        platform_pump(&plat);
        engine_update(platform_delta_seconds(&plat));
        engine_render();
        platform_swap(&plat);
    }

    // printf("Shutting down...");

    engine_shutdown();
    platform_shutdown(&plat);
    
    return 0;
}
