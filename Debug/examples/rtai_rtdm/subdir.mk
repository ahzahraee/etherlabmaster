################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/rtai_rtdm/main.c 

OBJS += \
./examples/rtai_rtdm/main.o 

C_DEPS += \
./examples/rtai_rtdm/main.d 


# Each subdirectory must supply rules for building sources it contributes
examples/rtai_rtdm/%.o: ../examples/rtai_rtdm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


