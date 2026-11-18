# sdlgs: the Apple IIGS (ROM 3) with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlgs --help
#
# The IIGS itself is esp32gs's (../esp32gs/components/apple2gs: its glue and
# Clemens's machine, platform independent), the runtime sdlemu's
# (../sdlemu), the 65C816 esp32emu's (../esp32emu): all four cloned side
# by side.
cmake_minimum_required(VERSION 3.20)
project(sdlgs C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32GS_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32gs" CACHE PATH "esp32gs checkout: the IIGS")
if(NOT EXISTS "${ESP32GS_DIR}/components/apple2gs/include/gs.h")
    message(FATAL_ERROR "No esp32gs at ${ESP32GS_DIR}: clone github.com/rlucencic/esp32gs beside sdlgs")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

set(GS "${ESP32GS_DIR}/components/apple2gs")
file(GLOB CLEMENS_SOURCES "${GS}/clemens/*.c")
add_executable(sdlgs
    src/main.c
    src/settings.c
    src/rom_store.c
    "${GS}/gs.c" "${GS}/video.c" "${GS}/storage.c"
    ${CLEMENS_SOURCES})
target_include_directories(sdlgs PRIVATE src "${GS}/include" "${GS}" "${GS}/clemens")
sdlemu_add_cores(sdlgs w65816 diskspace)
target_link_libraries(sdlgs PRIVATE sdlemu)
target_compile_options(sdlgs PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-result)
# Clemens as it comes: its warnings are its own (as esp32gs's)
set_source_files_properties(${CLEMENS_SOURCES} PROPERTIES COMPILE_OPTIONS "-w")

install(TARGETS sdlgs)
