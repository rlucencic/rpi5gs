# rpi5gs

An Apple IIGS (ROM 3) for the Raspberry Pi 5, in a window of its own:
[esp32gs](https://github.com/rlucencic/esp32gs)'s IIGS (Clemens's machine
with esp32emu's 65C816) on the [rpi5emu](https://github.com/rlucencic/rpi5emu)
runtime.

- GS/OS 6 from floppies (3.5" and 5.25": PO, 2MG, DSK, DO, WOZ) or hard
  disks (HDV, PO, 2MG), Super Hi-Res and all the Apple II modes, Ensoniq
  sound, 1 to 8 MB of RAM.
- The setup screen (memory, sound, the drives), the web page for the disk
  images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32gs and rpi5gs cloned side by side, then

```sh
cd rpi5gs && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

In the data folder's `roms/` (`~/rpi5emu/roms`), named as esp32gs's:
`gs_rom3.rom` (256 KB) and `chargen.rom` (4 KB). Not part of this
repository.

## Running

```sh
build/rpi5gs                          # the setup screen first
build/rpi5gs -S --choice Memory="4 MB"
build/rpi5gs System.Disk.po           # with a disk in the 3.5" drive
```

Disks live in `~/rpi5emu/apple2gs/`. The keyboard by position, as Apple's
ADB keyboard: Alt is Option, the Windows key Command (the open apple), F12
or Pause the Reset key (Control-F12: Control-Reset; Control-Command-Esc:
the control panel). The mouse after a click in the window.

## Licence

MIT.
