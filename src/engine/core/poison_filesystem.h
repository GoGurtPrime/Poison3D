#pragma once

#include <stdint.h>
#include <stddef.h>

// Reads an entire file into memory. 
// Populates out_size with the number of bytes read (if out_size is not NULL).
// Returns a dynamically allocated buffer that must be freed with free_asset_bytes.
uint8_t *read_asset_bytes(const char *path, size_t *out_size);

// Frees the memory allocated by read_asset_bytes.
void free_asset_bytes(uint8_t *buffer);
