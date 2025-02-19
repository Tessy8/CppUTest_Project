# Fetch ubuntu image
FROM ubuntu:22.04

# Install python on image
RUN apt-get update && apt-get install -y \
    gcc-arm-none-eabi \
    cmake \
    build-essential \
    autoconf \
    automake \
    libtool \
    git \
    wget \
    python3 \
    python3-dev \
    python3-pip \
    libusb-1.0-0-dev

# Set up environment variable
ENV PICO_SDK_PATH=/root/pico/pico-sdk

# Clone the Pico SDK version from git
RUN mkdir -p ${PICO_SDK_PATH} \
    && git clone https://github.com/raspberrypi/pico-sdk.git ${PICO_SDK_PATH} \
    && cd ${PICO_SDK_PATH} \
    && git submodule update --init

# Download and extract FreeRTOS-Kernel from raspberrypi
RUN wget https://github.com/raspberrypi/FreeRTOS-Kernel/archive/refs/heads/master.tar.gz -O FreeRTOS-Kernel-main.tar.gz \
    && mkdir -p /root/pico/FreeRTOS-Kernel \
    && tar -xzf FreeRTOS-Kernel-main.tar.gz -C /root/ \
    && mv /root/FreeRTOS-Kernel-main/* /root/pico/FreeRTOS-Kernel \
    && rm -rf FreeRTOS-Kernel-main.tar.gz /root/FreeRTOS-Kernel-main

WORKDIR /root/powerlabs

RUN mkdir /root/powerlabs/folder

# Download and extract FreeRTOS-Kernel version 10.6.0 using wget
RUN wget https://github.com/FreeRTOS/FreeRTOS-Kernel/archive/refs/tags/V10.6.0.tar.gz -O FreeRTOS-Kernel.tar.gz \
    && tar -xzf FreeRTOS-Kernel.tar.gz -C /root/powerlabs/folder/ \
    && mv /root/powerlabs/folder/FreeRTOS-Kernel-10.6.0 /root/powerlabs/folder/FreeRTOS-Kernel \
    && rm /root/powerlabs/FreeRTOS-Kernel.tar.gz

# Copy the project source code
COPY ./src /root/powerlabs/folder/src
COPY ./include /root/powerlabs/folder/include
COPY ./tests /root/powerlabs/folder/tests
COPY ./Makefile /root/powerlabs/folder/
COPY ./CMakeLists.txt /root/powerlabs/folder/
COPY ./pico_sdk_import.cmake /root/powerlabs/folder/ 
COPY ./README.md /root/powerlabs/folder/

# Execute script
ENTRYPOINT ["make", "firmware", "-C", "/root/powerlabs/folder/"]
