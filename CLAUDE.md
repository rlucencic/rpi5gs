# rpi5gs: the Apple IIGS on the Raspberry Pi 5

esp32gs's IIGS (`../esp32gs/components/apple2gs`: its glue and Clemens's
machine, platform independent) on the rpi5emu runtime (`../rpi5emu`, its
CLAUDE.md: the workflow, the Pi, the lessons), the 65C816 esp32emu's. The
machine's own behaviour, lessons and tests are esp32gs's CLAUDE.md; this
project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The IIGS as an `emu_machine_t`: esp32gs's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py`, then: memory up to 8 MB as on the Tab5, a new size allocated at the restart (the boards restart into it), the ROM message, no speaker stats; the core's host-build switches (`gs_host_no_iwm_skip`, ...) defined off |
| `src/settings.c` | esp32gs's, over `emu/nvs.h` (section `gs`: `ram_kb`, `bram` the battery RAM as hex) |
| `src/rom_store.c` | `~/rpi5emu/apple2gs/roms/` through `emu_rom_read()`: gs_rom3.rom, chargen.rom |

Keep `src/main.c` in step with esp32gs's `main/main.c`. The core's
`#ifndef ESP_PLATFORM` parts are its host test build's instrumentation
(I/O counters, the IWM switches): they're compiled in here too.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5gs build
../rpi5emu/tools/pi.sh rpi5gs headless     # or run: the window here
../rpi5emu/tools/console.sh 'K 36 1' @0.3 'K 7F 1' @0.3 'K 7F 0' @0.3 'K 36 0' @2 'T CATALOG\n'
../rpi5emu/tools/pi.sh rpi5gs shot out.png
```

Console: the runtime's (`h`) and esp32gs's: `k <hex>` tap an ADB key (24
Return, 31 space, 35 Esc), `K <hex> 0|1` (36 Control, 37 Command, 38
Shift, 3A Option, 7F Reset), `T <text>`, `m <dx> <dy> <btn>`, `g [hex n]`,
`R <MB>`. **Control-Reset's keys a frame apart** (the `@0.3` above): with
Reset's and Control's key-ups in one frame Control stayed down for the
IIGS, and the letters typed after it came out as control characters
(invisible), digits and Return as they are.

Checked on the Pi (2026-11-15, headless): ROM 3 at 100%, 60 frames a
second, "Check startup device!" without a disk; Control-Reset to Applesoft,
a line typed and run; the battery RAM kept in the settings. Not yet: the
window by hand, sound heard, GS/OS from a disk, the hard disks, more RAM.
