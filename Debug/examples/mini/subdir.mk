################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../examples/mini/ec_mini.mod.o \
../examples/mini/ec_mini.o \
../examples/mini/mini.o 

C_SRCS += \
../examples/mini/ec_mini.mod.c \
../examples/mini/mini.c \
../examples/mini/mini_ek1818.c 

OBJS += \
./examples/mini/ec_mini.mod.o \
./examples/mini/mini.o \
./examples/mini/mini_ek1818.o 

C_DEPS += \
./examples/mini/ec_mini.mod.d \
./examples/mini/mini.d \
./examples/mini/mini_ek1818.d 


# Each subdirectory must supply rules for building sources it contributes
examples/mini/%.o: ../examples/mini/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


