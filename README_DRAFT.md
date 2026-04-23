# STM32F4 Flight Controller Firmware

Bare-metal flight controller firmware for the STM32F4 Discovery board (STM32F407VGT6).
Built from scratch with CMake and a custom ARM toolchain — no STM32CubeIDE dependency.

## Architecture
- Custom CMake build system with arm-none-eabi-gcc toolchain
- CMSIS Core + Device headers as git submodules (official STMicroelectronics repos)
- STM32F4xx HAL with selective module inclusion
- Cortex-M4 with FPU: hard float ABI, fpv4-sp-d16

## Hardware
- STM32F4 Discovery (STM32F407VGT6)
  - 1MB Flash, 192KB RAM (128KB SRAM + 64KB CCMRAM)
  - Cortex-M4 @ up to 168MHz, single-precision FPU 

## Building
### Prerequisites
```bash
sudo apt install gcc-arm-none-eabi cmake ninja-build
```
### Clone and build
```bash
git clone --recurse-submodules https://github.com/pra-bean/fc-firmware.git
cd fc-firmware
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```
### Flash (OpenOCD + ST-Link)
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
        -c "program build/fc-firmware.elf verify reset exit"
```

## Status
Under active development. Current focus: peripheral driver layer.

## License
MIT
