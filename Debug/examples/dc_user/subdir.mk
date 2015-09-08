################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../examples/dc_user/ec_dc_user_example-main.o 

C_SRCS += \
../examples/dc_user/main.c 

OBJS += \
./examples/dc_user/main.o 

C_DEPS += \
./examples/dc_user/main.d 


# Each subdirectory must supply rules for building sources it contributes
examples/dc_user/%.o: ../examples/dc_user/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


