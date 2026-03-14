cmake_minimum_required(VERSION 3.20)

# Must be set before project()
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-none-eabi.cmake)

project(fc-firmware
    VERSION 0.1.0
    LANGUAGES C ASM
)

# Generate compile_commands.json for clangd/IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Build type default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# -------------------------------------------------------------------
# Compiler flags
# -------------------------------------------------------------------
set(COMMON_FLAGS
    -Wall
    -Wextra
    -Wshadow
    -fdata-sections        # Place each data item in its own section
    -ffunction-sections    # Place each function in its own section
    -fno-common
)

set(DEBUG_FLAGS   -Og -g3 -DDEBUG)
set(RELEASE_FLAGS -O2)

# -------------------------------------------------------------------
# Preprocessor defines
# -------------------------------------------------------------------
add_compile_definitions(
    STM32F407xx
    USE_HAL_DRIVER
)

# -------------------------------------------------------------------
# CMSIS & HAL include paths
# -------------------------------------------------------------------
set(CMSIS_CORE_INC      lib/cmsis_core/Include)
set(CMSIS_DEVICE_INC    lib/cmsis_device_f4/Include)
set(HAL_INC             lib/stm32f4xx_hal/Inc)

# -------------------------------------------------------------------
# HAL source files (only include what you use — add more as needed)
# -------------------------------------------------------------------
file(GLOB HAL_SOURCES
    lib/stm32f4xx_hal/Src/stm32f4xx_hal.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_cortex.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_rcc.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_gpio.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_uart.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_spi.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_tim.c
    lib/stm32f4xx_hal/Src/stm32f4xx_hal_dma.c
)

# -------------------------------------------------------------------
# Startup file & application sources
# -------------------------------------------------------------------
set(STARTUP_FILE lib/cmsis_device_f4/Source/Templates/gcc/startup_stm32f407xx.s)

file(GLOB_RECURSE APP_SOURCES
    src/*.c
)

# -------------------------------------------------------------------
# Firmware target
# -------------------------------------------------------------------
add_executable(${PROJECT_NAME}
    ${STARTUP_FILE}
    ${HAL_SOURCES}
    ${APP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMSIS_CORE_INC}
    ${CMSIS_DEVICE_INC}
    ${HAL_INC}
    src/
)

target_compile_options(${PROJECT_NAME} PRIVATE
    ${COMMON_FLAGS}
    $<$<CONFIG:Debug>:${DEBUG_FLAGS}>
    $<$<CONFIG:Release>:${RELEASE_FLAGS}>
)

# Linker
target_link_options(${PROJECT_NAME} PRIVATE
    -T${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld
    -Wl,--gc-sections           # Remove unused sections
    -Wl,-Map=${PROJECT_NAME}.map
    --specs=nano.specs          # Use newlib-nano (smaller)
    --specs=nosys.specs         # No OS syscalls
    -Wl,--print-memory-usage
)

# -------------------------------------------------------------------
# Post-build: generate .bin and print size
# -------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
            $<TARGET_FILE:${PROJECT_NAME}>
            ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Generating binary and printing size..."
)