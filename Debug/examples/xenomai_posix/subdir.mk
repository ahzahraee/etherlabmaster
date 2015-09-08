################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/xenomai_posix/main.c 

OBJS += \
./examples/xenomai_posix/main.o 

C_DEPS += \
./examples/xenomai_posix/main.d 


# Each subdirectory must supply rules for building sources it contributes
examples/xenomai_posix/%.o: ../examples/xenomai_posix/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


