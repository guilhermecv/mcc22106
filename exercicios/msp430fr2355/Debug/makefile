################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./02_main_simple_display_mux.obj" \
"./displays/simple_display_mux.obj" \
"../lnk_msp430fr2355.cmd" \
$(GEN_CMDS__FLAG) \
-lfrwp_init.a \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include displays/subdir_vars.mk
-include subdir_rules.mk
-include displays/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
msp430fr2355.out \

EXE_OUTPUTS__QUOTED += \
"msp430fr2355.out" \

BIN_OUTPUTS += \
msp430fr2355.hex \

BIN_OUTPUTS__QUOTED += \
"msp430fr2355.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "msp430fr2355.out"

# Tool invocations
msp430fr2355.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"/home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --advice:power=all --advice:hw_config=all --define=__MSP430FR2355__ --define=_FRWP_ENABLE --define=_INFO_FRWP_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"msp430fr2355.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"/home/guilherme/ti/ccs930/ccs/ccs_base/msp430/include" -i"/home/guilherme/ti/ccs930/ccs/ccs_base/msp430/lib/FR2xx" -i"/home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/lib" -i"/home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/include" --priority --reread_libs --define=_FRWP_ENABLE --define=_INFO_FRWP_ENABLE --diag_wrap=off --display_error_number --warn_sections --xml_link_info="msp430fr2355_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "msp430fr2355.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

msp430fr2355.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"/home/guilherme/ti/ccs930/ccs/tools/compiler/ti-cgt-msp430_18.12.4.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "msp430fr2355.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "02_main_simple_display_mux.obj" "displays/simple_display_mux.obj" 
	-$(RM) "02_main_simple_display_mux.d" "displays/simple_display_mux.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

