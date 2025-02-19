project(average_tests)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        master # or use release tag, eg. v4.0
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

# Add the source files for the component and the test files
FILE(GLOB COMPONENT_SOURCES ${SRC_DIR}/average.cpp)
FILE(GLOB TEST_SOURCES ${TEST_DIR}/average/*.cpp)
FILE(GLOB HOST_COMPONENT_SOURCES ${HOST_SRC_DIR}/average.cpp)

# Settings for host build
add_executable(average_tests ${HOST_COMPONENT_SOURCES} ${TEST_SOURCES} ${TEST_DIR}/syscalls.c)
target_link_libraries(average_tests
                    CppUTest::CppUTest
                    CppUTest::CppUTestExt
                    )  # Link CppUTest for unit tests
target_include_directories(average_tests PRIVATE   
                        ${HOST_INCLUDE_DIR}
                        )
target_compile_definitions(average_tests PRIVATE
                        CPPUTEST_HAVE_EXCEPTIONS=1
                        )