################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIODrv.c \
../DIO_prog.c \
../LCD.c \
../TX.c \
../USART_prog.c 

OBJS += \
./DIODrv.o \
./DIO_prog.o \
./LCD.o \
./TX.o \
./USART_prog.o 

C_DEPS += \
./DIODrv.d \
./DIO_prog.d \
./LCD.d \
./TX.d \
./USART_prog.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


