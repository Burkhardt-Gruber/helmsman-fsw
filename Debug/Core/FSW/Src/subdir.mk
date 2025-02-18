################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/FSW/Src/channel.cpp \
../Core/FSW/Src/example_wk.cpp \
../Core/FSW/Src/fsw_debug.cpp \
../Core/FSW/Src/fsw_ipc.cpp \
../Core/FSW/Src/fsw_main.cpp \
../Core/FSW/Src/message.cpp \
../Core/FSW/Src/nucleo_watchdog_wk.cpp \
../Core/FSW/Src/watchdog_wk.cpp \
../Core/FSW/Src/worker.cpp 

OBJS += \
./Core/FSW/Src/channel.o \
./Core/FSW/Src/example_wk.o \
./Core/FSW/Src/fsw_debug.o \
./Core/FSW/Src/fsw_ipc.o \
./Core/FSW/Src/fsw_main.o \
./Core/FSW/Src/message.o \
./Core/FSW/Src/nucleo_watchdog_wk.o \
./Core/FSW/Src/watchdog_wk.o \
./Core/FSW/Src/worker.o 

CPP_DEPS += \
./Core/FSW/Src/channel.d \
./Core/FSW/Src/example_wk.d \
./Core/FSW/Src/fsw_debug.d \
./Core/FSW/Src/fsw_ipc.d \
./Core/FSW/Src/fsw_main.d \
./Core/FSW/Src/message.d \
./Core/FSW/Src/nucleo_watchdog_wk.d \
./Core/FSW/Src/watchdog_wk.d \
./Core/FSW/Src/worker.d 


# Each subdirectory must supply rules for building sources it contributes
Core/FSW/Src/%.o Core/FSW/Src/%.su Core/FSW/Src/%.cyclo: ../Core/FSW/Src/%.cpp Core/FSW/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"/home/jimmy/Projects/School/SP/flightsoftware/Core/FSW/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -Wextra -Werror -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-FSW-2f-Src

clean-Core-2f-FSW-2f-Src:
	-$(RM) ./Core/FSW/Src/channel.cyclo ./Core/FSW/Src/channel.d ./Core/FSW/Src/channel.o ./Core/FSW/Src/channel.su ./Core/FSW/Src/example_wk.cyclo ./Core/FSW/Src/example_wk.d ./Core/FSW/Src/example_wk.o ./Core/FSW/Src/example_wk.su ./Core/FSW/Src/fsw_debug.cyclo ./Core/FSW/Src/fsw_debug.d ./Core/FSW/Src/fsw_debug.o ./Core/FSW/Src/fsw_debug.su ./Core/FSW/Src/fsw_ipc.cyclo ./Core/FSW/Src/fsw_ipc.d ./Core/FSW/Src/fsw_ipc.o ./Core/FSW/Src/fsw_ipc.su ./Core/FSW/Src/fsw_main.cyclo ./Core/FSW/Src/fsw_main.d ./Core/FSW/Src/fsw_main.o ./Core/FSW/Src/fsw_main.su ./Core/FSW/Src/message.cyclo ./Core/FSW/Src/message.d ./Core/FSW/Src/message.o ./Core/FSW/Src/message.su ./Core/FSW/Src/nucleo_watchdog_wk.cyclo ./Core/FSW/Src/nucleo_watchdog_wk.d ./Core/FSW/Src/nucleo_watchdog_wk.o ./Core/FSW/Src/nucleo_watchdog_wk.su ./Core/FSW/Src/watchdog_wk.cyclo ./Core/FSW/Src/watchdog_wk.d ./Core/FSW/Src/watchdog_wk.o ./Core/FSW/Src/watchdog_wk.su ./Core/FSW/Src/worker.cyclo ./Core/FSW/Src/worker.d ./Core/FSW/Src/worker.o ./Core/FSW/Src/worker.su

.PHONY: clean-Core-2f-FSW-2f-Src

