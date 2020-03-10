################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
teclado_matricial/%.obj: ../teclado_matricial/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="/home/guilherme/ti/ccs930/ccs/ccs_base/msp430/include" --include_path="/home/guilherme/Documentos/IFSC/mcc22106/exercicios/msp430fr2355" --include_path="/home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/include" --advice:power=all --define=__MSP430F2330__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="teclado_matricial/$(basename $(<F)).d_raw" --obj_directory="teclado_matricial" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


