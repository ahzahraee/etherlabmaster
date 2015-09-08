################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/libethercat_la-common.o \
../lib/libethercat_la-domain.o \
../lib/libethercat_la-master.o \
../lib/libethercat_la-reg_request.o \
../lib/libethercat_la-sdo_request.o \
../lib/libethercat_la-slave_config.o \
../lib/libethercat_la-voe_handler.o 

C_SRCS += \
../lib/common.c \
../lib/domain.c \
../lib/master.c \
../lib/reg_request.c \
../lib/sdo_request.c \
../lib/slave_config.c \
../lib/voe_handler.c 

OBJS += \
./lib/common.o \
./lib/domain.o \
./lib/master.o \
./lib/reg_request.o \
./lib/sdo_request.o \
./lib/slave_config.o \
./lib/voe_handler.o 

C_DEPS += \
./lib/common.d \
./lib/domain.d \
./lib/master.d \
./lib/reg_request.d \
./lib/sdo_request.d \
./lib/slave_config.d \
./lib/voe_handler.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


