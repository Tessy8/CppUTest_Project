# Embedded Devops for Pai-Hardware

## Table of Contents
1. [Introduction](#1-introduction)
2. [Creating a New Repository from this Template](#2-creating-a-new-repository-from-this-template)
3. [Integrating CI/CD into your Project](#3-integrating-cicd-into-your-project)
   - 3.1 [Key Files](#31-key-files)
   - 3.2 [Changes for CI/CD Integration](#32-changes-for-cicd-integration)
   - 3.3 [Testing with CppUTest](#33-testing-with-cpputest)
   - 3.4 [Building the Project](#34-building-the-project)
4. [Setting up Docker](#4-setting-up-docker)
   - 4.1 [Installing Docker](#41-installing-docker)
   - 4.2 [Building the Docker Image](#42-building-the-docker-image)
   - 4.3 [Running the Container](#43-running-the-container)

## 1. Introduction

This guide covers the essential DevOps setup for developing and deploying a project using an embedded Raspberry Pi Pico environment. By leveraging Docker and other CI/CD tools, we ensure that the development and deployment processes are streamlined and scalable. Additionally, this repository serves as a GitHub template, allowing users to quickly set up their own projects with a ready-made DevOps configuration tailored for embedded development for the Raspberry Pi Pico.

## 2. Creating a New Repository from this Template

- On the top right of the repository page, click 
the dropdown next to the green "Use this template" button.
- Click "Create a new repository".
- Fill in the repository details:
    - Repository name: Enter a name for your new repository.
    - Description: Optionally, add a short description.
    - Visibility: Choose between "Public" or "Private".
- Click the "Create repository" button to create your new repository.

## 3. Integrating CI/CD into your Project

To integrate CI/CD into your project, follow these steps:

### 3.1 Key Files

- `.github/workflows/pai-action.yml` (if using GitHub actions).
- `ci-cd-tools/Dockerfile`.
- `Makefile` (for managing builds for both host and ARM targets).

### 3.2 Changes for CI/CD Integration

- **pai-action.yml:**
    - Edit the uf2 file name in step 6 to your uf2 file name (this is optional. If you do this, you need to edit the project name in the CMakeLists.txt file in the root directory.)
    - You can also edit the file to suit your requirement (this is optional).
- **Dockerfile:**
    - Edit the Dockerfile to include the necessary environment setup for your CI/CD pipeline (Remove FreeRTOS-Kernel, if not needed).
    - Copy all source code and testing directories into the container and set the entry point to correctly build the firmware.
- **Makefile:**
    - Update the paths for SDK and build directories to ensure they match your project structure.
- **CMakeLists.txt:**
    - If you're adapting an existing repository to the template, include the tests directories as subdirectory.

### 3.3 Testing with CppUTest 

   Use the below project structure:

    ```
    tests/
    ├── host/
    │   ├── firstTest/          # First test on the host system
    │   |   └── CMakeLists.txt
    │   |   └── main.cpp
    │   |   └── test.cpp
    │   ├── include/            # Header files for host-based tests
    │   ├── src/                # Source files for host-based tests
    │   └── CMakeLists.txt      # Build configuration
    ├── target/
    │   ├── firstTest/            # Target-specific First test
    │   |   └── CMakeLists.txt
    │   |   └── main.cpp
    │   |   └── test.cpp
    ```

### 3.4 Building the Project

From the working directory,
- **Host:**
    - Run:
    ```bash
    make host_tests
    ```
    - To include tests, add each test directory to 'CMakeLists.txt' in the tests/host directory.
- **Target::**
    - Run:
    ```bash
    make firmware
    ```
    - To include tests, add each test directory to 'CMakeLists.txt' in the working directory.

## 4. Setting up Docker

To ensure a consistent development environment across different machines, we will use Docker to containerize the build and development process for Raspberry Pi Pico.

### 4.1 Installing Docker

First, you need to install Docker on your machine. The installation steps vary depending on your operating system.

- **For Ubuntu (Linux):**
    ```bash
    sudo apt update
    sudo apt install docker.io
    sudo systemctl start docker
    sudo systemctl enable docker
    sudo usermod -aG docker $USER
    ```

- **For other operating systems** (e.g., macOS or Windows), refer to the [official Docker installation guide](https://docs.docker.com/get-docker/).

After installation, verify Docker by running:

```bash
docker --version
```

### 4.2 Building the Docker Image

To build the Docker image using the `Dockerfile` created above run the following command in the terminal from the root directory where the `Dockerfile` is located:

```bash
docker build -t pai-build-env -f ./ci-cd-tools/Dockerfile .
```

This command will build a Docker image with the name `pai-build-env` using the instructions in the `Dockerfile`.

### 4.3 Running the Container

To run the container in interactive mode, use the following command:
```bash
docker create -i -t --entrypoint="/bin/bash" --name pico_build_container pai-build-env
docker start -i pico_build_container
```
Explanation:
- `-i`: Keeps the STDIN open for interaction.
- `-t`: Allocates a pseudo-TTY for a terminal interface.
- `--entrypoint="/bin/bash"`: Overrides the container's entrypoint to start in bash mode.
- `name pico_build_container`: Gives the container a specific name.
- `pico-build-env`: Name of the Docker image used.

### Other Useful Docker Commands
- `docker container rm pico_build_container`: For deleting a container
- `docker rmi pico-build-env:latest`: For removing the Docker image named `pico-build-env`. Use this command to delete the image if it's no longer needed or to rebuild it.
- `docker cp <container>:<absolute_path_to_file> <destination>` : Run this in a separate terminal for copying a file from the docker environment to your local system. PS: the docker container must be running and the absolute path to the file must be used.
- `docker ps -a`: To list all containers, including those that are stopped.
- `docker images`: To list all Docker images on your system.
- `docker start pico_build_container`: To start the specified container.
- `docker stop pico_build_container`: To stop the specified running container.
- `exit`: To exit the running container.

From here, the build scripts for the project can be executed.
