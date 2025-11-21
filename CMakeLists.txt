cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)


project(stm32_minimal C ASM)

set(CMAKE_C_STANDARD 11)

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(C_COMMON_FLAGS "-ffreestanding -fno-builtin -Wall -Wextra -O0 -g3")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} -O2 -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${MCU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} ${MCU_FLAGS} -Wl,--gc-sections -T${CMAKE_SOURCE_DIR}/linker/STM32F446RETX_FLASH.ld"
)

set(SRC_FILES
    app/startup/startup_stm32f446xx.s
    app/src/core/system_clock.c
    app/src/core/system_stm32f4xx.c
    app/src/main.c
)

add_executable(${PROJECT_NAME}.elf ${SRC_FILES})

# generate .bin
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating ${PROJECT_NAME}.bin"
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    app/include
)


target_compile_definitions(${PROJECT_NAME}.elf PRIVATE STM32F446xx)



# flash via OpenOCD
add_custom_target(flash
    COMMAND openocd
        -f board/st_nucleo_f4.cfg
        -c "program ${PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing ${PROJECT_NAME}.elf to Nucleo-F4"
)
