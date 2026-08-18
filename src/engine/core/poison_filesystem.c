#include "compiler.h"
#include "poison_filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(POISON_PLATFORM_WINDOWS)
    #include <windows.h>
#elif defined(POISON_PLATFORM_MAC)
    #include <mach-o/dyld.h>
#elif defined(POISON_PLATFORM_LINUX)
    #include <unistd.h>
#endif

#define MAX_PATH_LENGTH 1024

// Internal helper to build the correct absolute path string
static void get_absolute_asset_path(const char *relative_path, char *out_path, size_t max_len) {
#if defined(POISON_PLATFORM_N64)
    // N64 Libdragon
    snprintf(out_path, max_len, "rom:/%s", relative_path);

#elif defined(POISON_PLATFORM_DREAMCAST)
    // Dreamcast KallistiOS
    snprintf(out_path, max_len, "/pc/%s", relative_path);

#else
    // Desktop platforms: Resolve executable directory first
    char exe_dir[MAX_PATH_LENGTH];
    exe_dir[0] = '\0';

#if defined(POISON_PLATFORM_WINDOWS)
    GetModuleFileNameA(NULL, exe_dir, sizeof(exe_dir));
    
    // Strip executable name to get the directory
    char *last_slash = strrchr(exe_dir, '\\');
    if (!last_slash) last_slash = strrchr(exe_dir, '/');
    if (last_slash) *last_slash = '\0';

#elif defined(POISON_PLATFORM_LINUX)
    ssize_t count = readlink("/proc/self/exe", exe_dir, sizeof(exe_dir) - 1);

    if (count > 0) 
    {
        exe_dir[count] = '\0';
        char *last_slash = strrchr(exe_dir, '/');
        if (last_slash) *last_slash = '\0';
    }

#elif defined(POISON_PLATFORM_MAC)
    uint32_t size = sizeof(exe_dir);
    if (_NSGetExecutablePath(exe_dir, &size) == 0) 
    {
        char *last_slash = strrchr(exe_dir, '/');
        if (last_slash) *last_slash = '\0';
    }
#endif

    // Combine the executable directory, the assets folder, and the relative file path.
    // Note: Windows' fopen handles mixed slashes (C:\dir/assets/file.txt) perfectly fine.
    snprintf(out_path, max_len, "%s/assets/%s", exe_dir, relative_path);
#endif
}

uint8_t *read_asset_bytes(const char *path, size_t *out_size) 
{
    if (!path) return NULL;

    char full_path[MAX_PATH_LENGTH];
    get_absolute_asset_path(path, full_path, sizeof(full_path));

    FILE *file = fopen(full_path, "rb");
    if (!file) 
    {
        // Optional: printf("Failed to open file: %s\n", full_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (size < 0) 
    {
        fclose(file);
        return NULL;
    }

    uint8_t *buffer = (uint8_t *)malloc((size_t)size + 1);
    if (!buffer) 
    {
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, (size_t)size, file);
    if (bytes_read != (size_t)size) 
    {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[size] = '\0'; 

    if (out_size) 
    {
        *out_size = (size_t)size;
    }

    fclose(file);
    return buffer;
}

void free_asset_bytes(uint8_t *buffer) 
{
    if (buffer) free(buffer);
}