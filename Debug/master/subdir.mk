################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../master/cdev.o \
../master/coe_emerg_ring.o \
../master/datagram.o \
../master/datagram_pair.o \
../master/device.o \
../master/domain.o \
../master/ec_master.mod.o \
../master/ec_master.o \
../master/ethernet.o \
../master/fmmu_config.o \
../master/foe_request.o \
../master/fsm_change.o \
../master/fsm_coe.o \
../master/fsm_foe.o \
../master/fsm_master.o \
../master/fsm_pdo.o \
../master/fsm_pdo_entry.o \
../master/fsm_sii.o \
../master/fsm_slave.o \
../master/fsm_slave_config.o \
../master/fsm_slave_scan.o \
../master/fsm_soe.o \
../master/ioctl.o \
../master/mailbox.o \
../master/master.o \
../master/module.o \
../master/pdo.o \
../master/pdo_entry.o \
../master/pdo_list.o \
../master/reg_request.o \
../master/sdo.o \
../master/sdo_entry.o \
../master/sdo_request.o \
../master/slave.o \
../master/slave_config.o \
../master/soe_errors.o \
../master/soe_request.o \
../master/sync.o \
../master/sync_config.o \
../master/voe_handler.o 

C_SRCS += \
../master/cdev.c \
../master/coe_emerg_ring.c \
../master/datagram.c \
../master/datagram_pair.c \
../master/debug.c \
../master/device.c \
../master/domain.c \
../master/doxygen.c \
../master/ec_master.mod.c \
../master/ethernet.c \
../master/fmmu_config.c \
../master/foe_request.c \
../master/fsm_change.c \
../master/fsm_coe.c \
../master/fsm_foe.c \
../master/fsm_master.c \
../master/fsm_pdo.c \
../master/fsm_pdo_entry.c \
../master/fsm_sii.c \
../master/fsm_slave.c \
../master/fsm_slave_config.c \
../master/fsm_slave_scan.c \
../master/fsm_soe.c \
../master/ioctl.c \
../master/mailbox.c \
../master/master.c \
../master/module.c \
../master/pdo.c \
../master/pdo_entry.c \
../master/pdo_list.c \
../master/reg_request.c \
../master/rtdm-ioctl.c \
../master/rtdm.c \
../master/sdo.c \
../master/sdo_entry.c \
../master/sdo_request.c \
../master/slave.c \
../master/slave_config.c \
../master/soe_errors.c \
../master/soe_request.c \
../master/sync.c \
../master/sync_config.c \
../master/voe_handler.c 

OBJS += \
./master/cdev.o \
./master/coe_emerg_ring.o \
./master/datagram.o \
./master/datagram_pair.o \
./master/debug.o \
./master/device.o \
./master/domain.o \
./master/doxygen.o \
./master/ec_master.mod.o \
./master/ethernet.o \
./master/fmmu_config.o \
./master/foe_request.o \
./master/fsm_change.o \
./master/fsm_coe.o \
./master/fsm_foe.o \
./master/fsm_master.o \
./master/fsm_pdo.o \
./master/fsm_pdo_entry.o \
./master/fsm_sii.o \
./master/fsm_slave.o \
./master/fsm_slave_config.o \
./master/fsm_slave_scan.o \
./master/fsm_soe.o \
./master/ioctl.o \
./master/mailbox.o \
./master/master.o \
./master/module.o \
./master/pdo.o \
./master/pdo_entry.o \
./master/pdo_list.o \
./master/reg_request.o \
./master/rtdm-ioctl.o \
./master/rtdm.o \
./master/sdo.o \
./master/sdo_entry.o \
./master/sdo_request.o \
./master/slave.o \
./master/slave_config.o \
./master/soe_errors.o \
./master/soe_request.o \
./master/sync.o \
./master/sync_config.o \
./master/voe_handler.o 

C_DEPS += \
./master/cdev.d \
./master/coe_emerg_ring.d \
./master/datagram.d \
./master/datagram_pair.d \
./master/debug.d \
./master/device.d \
./master/domain.d \
./master/doxygen.d \
./master/ec_master.mod.d \
./master/ethernet.d \
./master/fmmu_config.d \
./master/foe_request.d \
./master/fsm_change.d \
./master/fsm_coe.d \
./master/fsm_foe.d \
./master/fsm_master.d \
./master/fsm_pdo.d \
./master/fsm_pdo_entry.d \
./master/fsm_sii.d \
./master/fsm_slave.d \
./master/fsm_slave_config.d \
./master/fsm_slave_scan.d \
./master/fsm_soe.d \
./master/ioctl.d \
./master/mailbox.d \
./master/master.d \
./master/module.d \
./master/pdo.d \
./master/pdo_entry.d \
./master/pdo_list.d \
./master/reg_request.d \
./master/rtdm-ioctl.d \
./master/rtdm.d \
./master/sdo.d \
./master/sdo_entry.d \
./master/sdo_request.d \
./master/slave.d \
./master/slave_config.d \
./master/soe_errors.d \
./master/soe_request.d \
./master/sync.d \
./master/sync_config.d \
./master/voe_handler.d 


# Each subdirectory must supply rules for building sources it contributes
master/%.o: ../master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


