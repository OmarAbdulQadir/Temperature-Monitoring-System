################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HAL/Temp_sensor/Temp_sensor_program.c 

OBJS += \
./Drivers/HAL/Temp_sensor/Temp_sensor_program.o 

C_DEPS += \
./Drivers/HAL/Temp_sensor/Temp_sensor_program.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HAL/Temp_sensor/%.o: ../Drivers/HAL/Temp_sensor/%.c Drivers/HAL/Temp_sensor/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


