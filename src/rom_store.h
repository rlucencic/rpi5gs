#pragma once

#include <stdbool.h>
#include <stdint.h>

/*
 * The IIGS's ROMs: files in the machine's roms/ folder (emu_rom_read()), named
 * as esp32gs's.
 */
typedef enum {
    ROM_GS3,                    /* gs_rom3.rom: ROM 3, 256 KB (341-0737 + 341-0749) */
    ROM_CHARGEN,                /* chargen.rom: the IIe enhanced video ROM, 4 KB (342-0265-A) */
    ROM_COUNT
} rom_id_t;

const char *rom_store_name(rom_id_t id);    /* "gs_rom3.rom" */
uint32_t rom_store_size(rom_id_t id);

/* The whole ROM into buf; false if there's none */
bool rom_store_load(rom_id_t id, uint8_t *buf);
