# Compiler settings
HOST_CXX = g++
ARM_CXX = arm-none-eabi-g++

# Directories
SRC_DIR = ./src
TEST_DIR = ./tests
INCLUDE_DIR = ./include
BUILD_DIR = ./build

# Architecture-specific build directories
ARM_BUILD_DIR = $(BUILD_DIR)/arm
HOST_BUILD_DIR = $(BUILD_DIR)/host

# Common flags
COMMON_FLAGS = -Wall -Wextra -I$(INCLUDE_DIR)

# Host compilation flags
HOST_CXXFLAGS = $(COMMON_FLAGS)

# ARM compilation flags
ARM_CXXFLAGS = $(COMMON_FLAGS) \
			   -mcpu=cortex-m0plus \
			   -mthumb \
			   -I$(PICO_SDK_PATH)/src/common/pico_base/include \
			   -I$(PICO_SDK_PATH)/src/rp2_common/hardware_gpio/include \
			   -I$(PICO_SDK_PATH)/src/common/pico_stdlib/include \
			   -I$(PICO_SDK_PATH)/src/boards/include \
			   -Ibuild/generated/pico_base
ARM_LDFLAGS = -L$(PICO_SDK_PATH)/build -lpico_stdlib

# Default target
.PHONY: all
all: host_tests firmware

# Create build directories
$(HOST_BUILD_DIR) $(ARM_BUILD_DIR):
	mkdir -p $@

# Build and run host tests
.PHONY: host_tests
host_tests: $(HOST_BUILD_DIR)
	cd $(HOST_BUILD_DIR) && \
	cmake ../../tests/host && \
	make

# Build firmware with tests
.PHONY: firmware
firmware: $(ARM_BUILD_DIR)
	cd $(ARM_BUILD_DIR) && \
	cmake -DCMAKE_TOOLCHAIN_FILE=$(PICO_SDK_PATH)/cmake/preload/toolchains/pico_arm_cortex_m0plus_gcc.cmake \
		-DPICO_SDK_PATH=$(PICO_SDK_PATH) ../.. && \
	make

# Clean everything
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Clean test builds
.PHONY: test_clean
test_clean:
	rm -rf $(HOST_BUILD_DIR)
	rm -rf $(ARM_BUILD_DIR)/tests