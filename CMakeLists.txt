# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# # Pico SDK Path (adjust as needed)
# PICO_SDK_PATH ?= /home/testimony/pico/pico-sdk

include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")
include($ENV{PICO_SDK_PATH}/../FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake) #for RP2040

project(embedded_devops_template C CXX ASM)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Set up variables for directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

FILE(GLOB src src/*.cpp)

# Tell CMake where to find the executable source file
add_executable(embedded_devops_template
    ${src}
)

target_include_directories(embedded_devops_template PRIVATE
                           ${CMAKE_CURRENT_LIST_DIR}    
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
                           )

target_link_libraries(embedded_devops_template
                        pico_stdlib
                        FreeRTOS-Kernel-Heap4
                        pico_multicore
                        hardware_gpio 
                        hardware_i2c 
                        hardware_uart 
                        hardware_adc 
                        hardware_flash 
                        hardware_dma 
                        hardware_spi 
                        hardware_irq
                        hardware_watchdog 
                        hardware_rtc)

# Include tests directory as subdirectory
add_subdirectory(tests/target/led)

# Enable usb output, disable uart output
pico_enable_stdio_usb(embedded_devops_template 1)
pico_enable_stdio_uart(embedded_devops_template 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(embedded_devops_template)