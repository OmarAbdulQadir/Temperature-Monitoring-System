################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/Alarm.c \
../SRC/LCDdisp.c \
../SRC/TempUpdate.c \
../SRC/UserInput.c \
../SRC/main.c 

OBJS += \
./SRC/Alarm.o \
./SRC/LCDdisp.o \
./SRC/TempUpdate.o \
./SRC/UserInput.o \
./SRC/main.o 

C_DEPS += \
./SRC/Alarm.d \
./SRC/LCDdisp.d \
./SRC/TempUpdate.d \
./SRC/UserInput.d \
./SRC/main.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/%.o: ../SRC/%.c SRC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


