################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tty/subdir.mk
-include tool/subdir.mk
-include master/subdir.mk
-include lib/.libs/subdir.mk
-include lib/subdir.mk
-include examples/xenomai_posix/subdir.mk
-include examples/xenomai/subdir.mk
-include examples/user/subdir.mk
-include examples/tty/subdir.mk
-include examples/rtai_rtdm_dc/subdir.mk
-include examples/rtai_rtdm/subdir.mk
-include examples/rtai/subdir.mk
-include examples/mini/subdir.mk
-include examples/dc_user/subdir.mk
-include examples/dc_rtai/subdir.mk
-include devices/e1000e/subdir.mk
-include devices/e1000/subdir.mk
-include devices/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: etherlabmaster-1.5.2

# Tool invocations
etherlabmaster-1.5.2: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc  -o "etherlabmaster-1.5.2" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) etherlabmaster-1.5.2
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
