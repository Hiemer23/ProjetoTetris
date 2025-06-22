################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EEPROM.c \
../Core/Src/LCD_Manager.c \
../Core/Src/ManagerTetris.c \
../Core/Src/MatrizLed.c \
../Core/Src/input.c \
../Core/Src/lcdDisplay.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tetris.c 

OBJS += \
./Core/Src/EEPROM.o \
./Core/Src/LCD_Manager.o \
./Core/Src/ManagerTetris.o \
./Core/Src/MatrizLed.o \
./Core/Src/input.o \
./Core/Src/lcdDisplay.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tetris.o 

C_DEPS += \
./Core/Src/EEPROM.d \
./Core/Src/LCD_Manager.d \
./Core/Src/ManagerTetris.d \
./Core/Src/MatrizLed.d \
./Core/Src/input.d \
./Core/Src/lcdDisplay.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tetris.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/EEPROM.cyclo ./Core/Src/EEPROM.d ./Core/Src/EEPROM.o ./Core/Src/EEPROM.su ./Core/Src/LCD_Manager.cyclo ./Core/Src/LCD_Manager.d ./Core/Src/LCD_Manager.o ./Core/Src/LCD_Manager.su ./Core/Src/ManagerTetris.cyclo ./Core/Src/ManagerTetris.d ./Core/Src/ManagerTetris.o ./Core/Src/ManagerTetris.su ./Core/Src/MatrizLed.cyclo ./Core/Src/MatrizLed.d ./Core/Src/MatrizLed.o ./Core/Src/MatrizLed.su ./Core/Src/input.cyclo ./Core/Src/input.d ./Core/Src/input.o ./Core/Src/input.su ./Core/Src/lcdDisplay.cyclo ./Core/Src/lcdDisplay.d ./Core/Src/lcdDisplay.o ./Core/Src/lcdDisplay.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tetris.cyclo ./Core/Src/tetris.d ./Core/Src/tetris.o ./Core/Src/tetris.su

.PHONY: clean-Core-2f-Src

