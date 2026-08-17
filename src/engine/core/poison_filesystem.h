#pragma once

#include <stdint.h>
#include <stddef.h>

uint8_t *read_asset_bytes(const char *path, size_t *out_size);

void free_asset_bytes(uint8_t *buffer);
