# rpi5gs: the Apple IIGS (ROM 3) on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5gs --help
#
# The IIGS itself is esp32gs's (../esp32gs/components/apple2gs: its glue and
# Clemens's machine, platform independent), the runtime rpi5emu's
# (../rpi5emu), the 65C816 esp32emu's (../esp32emu): all four cloned side
# by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5gs C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32GS_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32gs" CACHE PATH "esp32gs checkout: the IIGS")
if(NOT EXISTS "${ESP32GS_DIR}/components/apple2gs/include/gs.h")
    message(FATAL_ERROR "No esp32gs at ${ESP32GS_DIR}: clone github.com/rlucencic/esp32gs beside rpi5gs")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

set(GS "${ESP32GS_DIR}/components/apple2gs")
file(GLOB CLEMENS_SOURCES "${GS}/clemens/*.c")
add_executable(rpi5gs
    src/main.c
    src/settings.c
    src/rom_store.c
    "${GS}/gs.c" "${GS}/video.c" "${GS}/storage.c"
    ${CLEMENS_SOURCES})
target_include_directories(rpi5gs PRIVATE src "${GS}/include" "${GS}" "${GS}/clemens")
rpi5emu_add_cores(rpi5gs w65816 diskspace)
target_link_libraries(rpi5gs PRIVATE rpi5emu)
target_compile_options(rpi5gs PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)
# Clemens as it comes: its warnings are its own (as esp32gs's)
set_source_files_properties(${CLEMENS_SOURCES} PROPERTIES COMPILE_OPTIONS "-w")

install(TARGETS rpi5gs)
