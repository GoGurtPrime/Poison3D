#include <stdio.h>
#include "../../platforms/platform.h"
#include "../../engine/core/engine.h"
#include <stdio.h>
#include "../../engine/filesystem/poison_filesystem.h"

void test_filesystem() {
    size_t file_size = 0;
    
    // Attempt to load the asset
    uint8_t *file_data = read_asset_bytes("test.txt", &file_size);

    if (file_data != NULL) {
        // 1. Print the size (%zu is the format specifier for size_t)
        printf("Success! Loaded asset 'test.txt'.\n");
        printf("Size: %zu bytes\n", file_size);
        
        // 2. Print the content
        printf("--- CONTENT START ---\n");
        printf("%s\n", (char *)file_data);
        printf("--- CONTENT END ---\n");
        
        // 3. Clean up memory
        free_asset_bytes(file_data);
    } else {
        printf("ERROR: Failed to load 'test.txt'.\n");
    }
}

int main(void) {
    Platform plat = {0};

    test_filesystem();

    // printf("Starting platform");
    if (!platform_init(&plat, "Poison3D Sandbox", 640, 480)) 
    {
        printf("Fatal error: Platform failed to init. (main.c)");

        return 1;
    }

    EngineConfig cfg = { plat.width, plat.height };
    engine_init(&cfg);

    while (plat.running) {
        platform_pump(&plat);
        engine_update(platform_delta_seconds(&plat));
        engine_render();
        platform_swap(&plat);
    }

    engine_shutdown();
    platform_shutdown(&plat);
    
    return 0;
}
