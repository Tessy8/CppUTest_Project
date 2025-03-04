project(trafficlight_test)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    # GIT_TAG        master # or use release tag, eg. v4.0
    GIT_TAG        667e69913f125aa184295ba271407845440f8b9a
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

set(TARGET_TEST_DIR ${TEST_DIR}/target)

# Add the source files for the component and the test files
FILE(GLOB COMPONENT_SOURCES ${SRC_DIR}/traffic_light.cpp)
FILE(GLOB TEST_SOURCES ${TARGET_TEST_DIR}/trafficlight/*.cpp)

# Settings for target
set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Settings for Pico build
add_executable(trafficlight_test ${COMPONENT_SOURCES} ${TEST_SOURCES})
target_link_libraries(trafficlight_test
                    pico_stdlib
                    pico_stdio_uart
                    hardware_gpio
                    CppUTest::CppUTest
                    CppUTest::CppUTestExt
                    )
target_include_directories(trafficlight_test PRIVATE   
                        ${INCLUDE_DIR}
                        )
target_compile_definitions(trafficlight_test PRIVATE
                        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
                        CPPUTEST_HAVE_EXCEPTIONS=1
                        )
                        
pico_enable_stdio_usb(trafficlight_test 1)
pico_enable_stdio_uart(trafficlight_test 0)

pico_add_extra_outputs(trafficlight_test)  # Generate .uf2, .hex, etc.
