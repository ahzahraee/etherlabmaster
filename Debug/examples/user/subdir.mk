################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../examples/user/ec_user_example-main.o 

C_SRCS += \
../examples/user/main.c \
../examples/user/main_ek1818.c 

OBJS += \
./examples/user/main.o \
./examples/user/main_ek1818.o 

C_DEPS += \
./examples/user/main.d \
./examples/user/main_ek1818.d 


# Each subdirectory must supply rules for building sources it contributes
examples/user/%.o: ../examples/user/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


