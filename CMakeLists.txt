cmake_minimum_required(VERSION 3.18.4)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(circle C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME} main.c Thread.c DrawBezier.c font_data.c Reverse.c SineWave.c SetPixel.c)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_spi
    hardware_dma
    pico_multicore
)

pico_add_extra_outputs(${PROJECT_NAME})
