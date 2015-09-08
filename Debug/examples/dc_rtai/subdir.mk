################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/dc_rtai/dc_rtai_sample.c 

OBJS += \
./examples/dc_rtai/dc_rtai_sample.o 

C_DEPS += \
./examples/dc_rtai/dc_rtai_sample.d 


# Each subdirectory must supply rules for building sources it contributes
examples/dc_rtai/%.o: ../examples/dc_rtai/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


