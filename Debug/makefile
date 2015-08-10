################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5

ORDERED_OBJS += \
"./hal_LCD.obj" \
"./main.obj" \
"./taos_mode.obj" \
"./driverlib/MSP430FR5xx_6xx/adc12_b.obj" \
"./driverlib/MSP430FR5xx_6xx/aes256.obj" \
"./driverlib/MSP430FR5xx_6xx/comp_e.obj" \
"./driverlib/MSP430FR5xx_6xx/crc.obj" \
"./driverlib/MSP430FR5xx_6xx/crc32.obj" \
"./driverlib/MSP430FR5xx_6xx/cs.obj" \
"./driverlib/MSP430FR5xx_6xx/dma.obj" \
"./driverlib/MSP430FR5xx_6xx/esi.obj" \
"./driverlib/MSP430FR5xx_6xx/eusci_a_spi.obj" \
"./driverlib/MSP430FR5xx_6xx/eusci_a_uart.obj" \
"./driverlib/MSP430FR5xx_6xx/eusci_b_i2c.obj" \
"./driverlib/MSP430FR5xx_6xx/eusci_b_spi.obj" \
"./driverlib/MSP430FR5xx_6xx/framctl.obj" \
"./driverlib/MSP430FR5xx_6xx/gpio.obj" \
"./driverlib/MSP430FR5xx_6xx/lcd_c.obj" \
"./driverlib/MSP430FR5xx_6xx/mpu.obj" \
"./driverlib/MSP430FR5xx_6xx/mpy32.obj" \
"./driverlib/MSP430FR5xx_6xx/pmm.obj" \
"./driverlib/MSP430FR5xx_6xx/ram.obj" \
"./driverlib/MSP430FR5xx_6xx/ref_a.obj" \
"./driverlib/MSP430FR5xx_6xx/rtc_b.obj" \
"./driverlib/MSP430FR5xx_6xx/rtc_c.obj" \
"./driverlib/MSP430FR5xx_6xx/sfr.obj" \
"./driverlib/MSP430FR5xx_6xx/sysctl.obj" \
"./driverlib/MSP430FR5xx_6xx/timer_a.obj" \
"./driverlib/MSP430FR5xx_6xx/timer_b.obj" \
"./driverlib/MSP430FR5xx_6xx/tlv.obj" \
"./driverlib/MSP430FR5xx_6xx/wdt_a.obj" \
"../lnk_msp430fr6989.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-l"libmath.a" \
-l"libc.a" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include driverlib/MSP430FR5xx_6xx/subdir_vars.mk
-include subdir_rules.mk
-include driverlib/MSP430FR5xx_6xx/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
biosentinel_optics_gse_2.out \

EXE_OUTPUTS__QUOTED += \
"biosentinel_optics_gse_2.out" \

BIN_OUTPUTS += \
biosentinel_optics_gse_2.txt \

BIN_OUTPUTS__QUOTED += \
"biosentinel_optics_gse_2.txt" \


# All Target
all: biosentinel_optics_gse_2.out secondary-outputs

# Tool invocations
biosentinel_optics_gse_2.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --advice:power=all --advice:hw_config=all -g --define=__MSP430FR6989__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal -z -m"biosentinel_optics_gse_2.map" --heap_size=400 --stack_size=400 --cinit_hold_wdt=on -i"/home/developer/ti/ccsv6/ccs_base/msp430/include" -i"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/lib" -i"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" -i"/home/developer/ti/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"/home/developer/ti/ccsv6/ccs_base/msp430/lib/FR59xx" --reread_libs --priority --define=_MPU_ENABLE --warn_sections --display_error_number --diag_wrap=off --xml_link_info="biosentinel_optics_gse_2_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "biosentinel_optics_gse_2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

biosentinel_optics_gse_2.txt: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/hex430" --memwidth=8 --romwidth=8 --ti_txt -o "biosentinel_optics_gse_2.txt" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "hal_LCD.pp" "main.pp" "taos_mode.pp" "driverlib/MSP430FR5xx_6xx/adc12_b.pp" "driverlib/MSP430FR5xx_6xx/aes256.pp" "driverlib/MSP430FR5xx_6xx/comp_e.pp" "driverlib/MSP430FR5xx_6xx/crc.pp" "driverlib/MSP430FR5xx_6xx/crc32.pp" "driverlib/MSP430FR5xx_6xx/cs.pp" "driverlib/MSP430FR5xx_6xx/dma.pp" "driverlib/MSP430FR5xx_6xx/esi.pp" "driverlib/MSP430FR5xx_6xx/eusci_a_spi.pp" "driverlib/MSP430FR5xx_6xx/eusci_a_uart.pp" "driverlib/MSP430FR5xx_6xx/eusci_b_i2c.pp" "driverlib/MSP430FR5xx_6xx/eusci_b_spi.pp" "driverlib/MSP430FR5xx_6xx/framctl.pp" "driverlib/MSP430FR5xx_6xx/gpio.pp" "driverlib/MSP430FR5xx_6xx/lcd_c.pp" "driverlib/MSP430FR5xx_6xx/mpu.pp" "driverlib/MSP430FR5xx_6xx/mpy32.pp" "driverlib/MSP430FR5xx_6xx/pmm.pp" "driverlib/MSP430FR5xx_6xx/ram.pp" "driverlib/MSP430FR5xx_6xx/ref_a.pp" "driverlib/MSP430FR5xx_6xx/rtc_b.pp" "driverlib/MSP430FR5xx_6xx/rtc_c.pp" "driverlib/MSP430FR5xx_6xx/sfr.pp" "driverlib/MSP430FR5xx_6xx/sysctl.pp" "driverlib/MSP430FR5xx_6xx/timer_a.pp" "driverlib/MSP430FR5xx_6xx/timer_b.pp" 
	-$(RM) "driverlib/MSP430FR5xx_6xx/tlv.pp" "driverlib/MSP430FR5xx_6xx/wdt_a.pp" 
	-$(RM) "hal_LCD.obj" "main.obj" "taos_mode.obj" "driverlib/MSP430FR5xx_6xx/adc12_b.obj" "driverlib/MSP430FR5xx_6xx/aes256.obj" "driverlib/MSP430FR5xx_6xx/comp_e.obj" "driverlib/MSP430FR5xx_6xx/crc.obj" "driverlib/MSP430FR5xx_6xx/crc32.obj" "driverlib/MSP430FR5xx_6xx/cs.obj" "driverlib/MSP430FR5xx_6xx/dma.obj" "driverlib/MSP430FR5xx_6xx/esi.obj" "driverlib/MSP430FR5xx_6xx/eusci_a_spi.obj" "driverlib/MSP430FR5xx_6xx/eusci_a_uart.obj" "driverlib/MSP430FR5xx_6xx/eusci_b_i2c.obj" "driverlib/MSP430FR5xx_6xx/eusci_b_spi.obj" "driverlib/MSP430FR5xx_6xx/framctl.obj" "driverlib/MSP430FR5xx_6xx/gpio.obj" "driverlib/MSP430FR5xx_6xx/lcd_c.obj" "driverlib/MSP430FR5xx_6xx/mpu.obj" "driverlib/MSP430FR5xx_6xx/mpy32.obj" "driverlib/MSP430FR5xx_6xx/pmm.obj" "driverlib/MSP430FR5xx_6xx/ram.obj" "driverlib/MSP430FR5xx_6xx/ref_a.obj" "driverlib/MSP430FR5xx_6xx/rtc_b.obj" "driverlib/MSP430FR5xx_6xx/rtc_c.obj" "driverlib/MSP430FR5xx_6xx/sfr.obj" "driverlib/MSP430FR5xx_6xx/sysctl.obj" "driverlib/MSP430FR5xx_6xx/timer_a.obj" 
	-$(RM) "driverlib/MSP430FR5xx_6xx/timer_b.obj" "driverlib/MSP430FR5xx_6xx/tlv.obj" "driverlib/MSP430FR5xx_6xx/wdt_a.obj" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

