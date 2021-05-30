################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/batProtect.c \
../Core/Src/main.c \
../Core/Src/stm32l0xx_hal_msp.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32l0xx.c 

OBJS += \
./Core/Src/batProtect.o \
./Core/Src/main.o \
./Core/Src/stm32l0xx_hal_msp.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32l0xx.o 

C_DEPS += \
./Core/Src/batProtect.d \
./Core/Src/main.d \
./Core/Src/stm32l0xx_hal_msp.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32L021xx -I"C:/Users/Marco/OneDrive - TBZ/IPA/02_Eigene_Unterlagen/SW_New/BatteryProtector/Core/Inc" -I"C:/Users/Marco/OneDrive - TBZ/IPA/02_Eigene_Unterlagen/SW_New/BatteryProtector/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/Marco/OneDrive - TBZ/IPA/02_Eigene_Unterlagen/SW_New/BatteryProtector/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Marco/OneDrive - TBZ/IPA/02_Eigene_Unterlagen/SW_New/BatteryProtector/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/Marco/OneDrive - TBZ/IPA/02_Eigene_Unterlagen/SW_New/BatteryProtector/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


