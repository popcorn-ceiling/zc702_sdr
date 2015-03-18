################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Common/subdir.mk
-include src/ADF4351/subdir.mk
-include src/AD9643/subdir.mk
-include src/AD9548/subdir.mk
-include src/AD9523/subdir.mk
-include src/AD9122/subdir.mk
-include src/AD8366/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
sdr_sw.elf.size \


# All Target
all: sdr_sw.elf secondary-outputs

# Tool invocations
sdr_sw.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM gcc linker'
	arm-xilinx-eabi-gcc -L"H:\sdr\zc702_sdr\sdr_sw_bsp\ps7_cortexa9_0\lib" -Wl,-T -Wl,../src/lscript.ld -L../../sdr_sw_bsp/ps7_cortexa9_0/lib -o "sdr_sw.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

sdr_sw.elf.size: sdr_sw.elf
	@echo 'Invoking: ARM Print Size'
	arm-xilinx-eabi-size sdr_sw.elf  |tee "sdr_sw.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(S_UPPER_DEPS) sdr_sw.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
