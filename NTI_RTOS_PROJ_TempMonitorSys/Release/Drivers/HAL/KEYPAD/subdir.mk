################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HAL/KEYPAD/KEYPAD_program.c 

OBJS += \
./Drivers/HAL/KEYPAD/KEYPAD_program.o 

C_DEPS += \
./Drivers/HAL/KEYPAD/KEYPAD_program.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HAL/KEYPAD/%.o: ../Drivers/HAL/KEYPAD/%.c Drivers/HAL/KEYPAD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

