################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/tty/serial.c \
../examples/tty/tty.c 

OBJS += \
./examples/tty/serial.o \
./examples/tty/tty.o 

C_DEPS += \
./examples/tty/serial.d \
./examples/tty/tty.d 


# Each subdirectory must supply rules for building sources it contributes
examples/tty/%.o: ../examples/tty/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


