################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
hal_LCD.obj: ../hal_LCD.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/home/developer/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --include_path="/home/developer/workspace_v6_0/biosentinel_optics_gse_2/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all -g --define=__MSP430FR6989__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="hal_LCD.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/home/developer/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --include_path="/home/developer/workspace_v6_0/biosentinel_optics_gse_2/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all -g --define=__MSP430FR6989__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

taos_mode.obj: ../taos_mode.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/home/developer/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/developer/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --include_path="/home/developer/workspace_v6_0/biosentinel_optics_gse_2/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all -g --define=__MSP430FR6989__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="taos_mode.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


