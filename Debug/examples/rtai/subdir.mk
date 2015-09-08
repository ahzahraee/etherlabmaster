################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/rtai/rtai_sample.c 

OBJS += \
./examples/rtai/rtai_sample.o 

C_DEPS += \
./examples/rtai/rtai_sample.d 


# Each subdirectory must supply rules for building sources it contributes
examples/rtai/%.o: ../examples/rtai/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


