menu "Motor Control"

config DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
    bool "Dual Shunt FOC Small Hurst Motor using PLL Control (with internal Op-Amp)"
    set DRV_ADC_USE_DRIVER_NEEDED to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_INTERRUPT_MODE to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_POLLED_MODE to n if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLOCK_DIVIDER to 4 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_WARMUP_CLOCK to "ADCHS_WARMUP_CLOCK_32" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_INTERRUPT_SOURCE to "INT_SOURCE_ADC_1_DATA0" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_INTERRUPT_VECTOR to "INT_VECTOR_ADC1_DATA0" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_INST_IDX0 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHNL_0_ALT_INP_SEL_IDX0 to "ADCHS_ALTERNATE_1_CLASS1_AN3" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_TRIGGER_SOURCE_IDX0 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_CLOCK_DIVIDER_IDX0 to 4 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_SAMPLE_TIME_COUNT_IDX0 to 2 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_INST_IDX1 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_ID_IDX1 to "ADCHS_CHANNEL_4" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHNL_4_ALT_INP_SEL_IDX1 to "ADCHS_ALTERNATE_3_CLASS1_AN0a" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_TRIGGER_SOURCE_IDX1 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_CLOCK_DIVIDER_IDX1 to 4 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_ADCHS_SAMPLE_TIME_COUNT_IDX1 to 2 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_INST_IDX2 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_ID_IDX2 to "ADCHS_CHANNEL_7" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_CLOCK_DIVIDER_IDX2 to 4 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_ADCHS_SAMPLE_TIME_COUNT_IDX2 to 2 if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_INST_IDX0 to  y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_IDX0 to "ADCHS_CLASS2_AN10" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_TRIGGER_SOURCE_IDX0 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_INST_IDX1 to  y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_IDX1 to "ADCHS_CLASS2_AN15" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_TRIGGER_SOURCE_IDX1 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}
	set USE_DRV_CMP to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}  
	set DRV_CMP_INST_IDX0 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_PERIPHERAL_ID_IDX0 to "CMP_ID_3" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_OUTPUT_ENABLE_IDX0 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_OPAMP_ENABLE_IDX0 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_INVERTING_INPUT_IDX0 to "CMP_INVERTING_INPUT_4" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_CMP_NON_INVERTING_INPUT_IDX0 to "CMP_NON_INVERTING_INPUT_CDAC" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_CMP_INST_IDX1 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_PERIPHERAL_ID_IDX1 to "CMP_ID_2" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_OPAMP_ENABLE_IDX1 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_INVERTING_INPUT_IDX1 to "CMP_INVERTING_INPUT_1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_CMP_NON_INVERTING_INPUT_IDX1 to "CMP_NON_INVERTING_INPUT_1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_CMP_INST_IDX2 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_OPAMP_ENABLE_IDX2 to y if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
    set DRV_CMP_INVERTING_INPUT_IDX2 to "CMP_INVERTING_INPUT_1" if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 
	set DRV_CMP_NON_INVERTING_INPUT_IDX2 to "CMP_NON_INVERTING_INPUT_1"	if DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE} 	
	default n
	---help---
	<!DOCTYPE HTML>
	<html>
	<h2>MPLAB Harmony Dual Shunt FOC SH Motor with PLL control Application Template</h2>
	<p>	This template generates a code example that exercises Dual Shunt 
	FOC SH Motor with PLL control with the following MHC options:</p>
	<br><b>- ADC Driver </b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Implementation: STATIC</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Mode: Interrupt</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Warmup Clock: ADCHS_WARMUP_CLOCK_32</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Interrupt Source: ADC1_DATA0</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Interrupt Vector: ADC1_DATA0</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Number of ADC Channels: 3</br>
	<br><b>&nbsp&nbsp - Channel 0 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - ADC instance: SAR0</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Alternate Input: ADCHS_ALTERNATE_1_CLASS1_AN3</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Trigger Source: ADCHS_TRIGGER_SOURCE_PWM1</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>
	<br><b>&nbsp&nbsp - Channel 1 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - ADC instance: SAR4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Alternate Input: ADCHS_ALTERNATE_3_CLASS1_AN0a</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Trigger Source: ADCHS_TRIGGER_SOURCE_PWM1</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>
	<br><b>&nbsp&nbsp - Channel 2 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - ADC instance: SAR7</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>	
	<br>&nbsp&nbsp&nbsp&nbsp - Inputs (class-2): ADCHS_CLASS2_AN10, ADCHS_CLASS2_AN15 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Triggers: PWM1 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>	
	<br><b>- CMP Driver</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Implementation: STATIC</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Mode: Polling</br>
	<br><b>&nbsp&nbsp - Channel 0 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - Module: CMP_ID_3 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Op-Amp: Enabled 2</br>	
	<br>&nbsp&nbsp&nbsp&nbsp - Inverting Input: CMP_INVERTING_INPUT_4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Non-Inverting Input: CMP_NON_INVERTING_INPUT_CDAC </br>
	<br><b>&nbsp&nbsp - Channel 1 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - Module: CMP_ID_2 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Op-Amp: Enabled 2</br>	
	<br>&nbsp&nbsp&nbsp&nbsp - Inverting Input: CMP_INVERTING_INPUT_1</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Non-Inverting Input: CMP_NON_INVERTING_INPUT_1 </br>
	<br><b>&nbsp&nbsp - Channel 2 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - Module: CMP_ID_1 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Comparator Output: Enabled</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Op-Amp: Enabled 2</br>	
	<br>&nbsp&nbsp&nbsp&nbsp - Inverting Input: CMP_INVERTING_INPUT_1</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Non-Inverting Input: CMP_NON_INVERTING_INPUT_1 </br>	
	<p>All other ADC and PWM driver configuration options are set to their 
	default values. 
	<p>The ADC driver configuration may be modified by 
	the user using MHC, under Harmony Framework Configuration -> Drivers - > ADC</p>
	<p>The PWM driver configuration may be modified by 
	the user using MHC, under Harmony Framework Configuration -> Drivers - > PWM</p></html>
	---endhelp---

config DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
    bool "Dual Shunt FOC Small Hurst Motor using PLL Control (with external Op-Amp)"
    set DRV_ADC_USE_DRIVER_NEEDED to y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_INTERRUPT_MODE to y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_POLLED_MODE to n if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLOCK_DIVIDER to 4 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_WARMUP_CLOCK to "ADCHS_WARMUP_CLOCK_32" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_INTERRUPT_SOURCE to "INT_SOURCE_ADC_1_DATA0" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_INTERRUPT_VECTOR to "INT_VECTOR_ADC1_DATA0" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_INST_IDX0 to y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHNL_0_ALT_INP_SEL_IDX0 to "ADCHS_ALTERNATE_3_CLASS1_AN24" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_TRIGGER_SOURCE_IDX0 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_CLOCK_DIVIDER_IDX0 to 4 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_SAMPLE_TIME_COUNT_IDX0 to 2 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_INST_IDX1 to y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_ID_IDX1 to "ADCHS_CHANNEL_4" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHNL_4_ALT_INP_SEL_IDX1 to "ADCHS_ALTERNATE_2_CLASS2_AN9" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_TRIGGER_SOURCE_IDX1 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_CLOCK_DIVIDER_IDX1 to 4 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE} 
	set DRV_ADCHS_SAMPLE_TIME_COUNT_IDX1 to 2 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_INST_IDX2 to y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_ID_IDX2 to "ADCHS_CHANNEL_7" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CHANNEL_CLOCK_DIVIDER_IDX2 to 4 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE} 
	set DRV_ADCHS_SAMPLE_TIME_COUNT_IDX2 to 2 if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_INST_IDX0 to  y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_IDX0 to "ADCHS_CLASS2_AN10" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_TRIGGER_SOURCE_IDX0 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_INST_IDX1 to  y if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_ANALOG_INPUT_IDX1 to "ADCHS_CLASS2_AN15" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}
	set DRV_ADCHS_CLASS_2_TRIGGER_SOURCE_IDX1 to "ADCHS_TRIGGER_SOURCE_PWM1" if DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}	
	default n
	---help---
	<!DOCTYPE HTML>
	<html>
	<h2>MPLAB Harmony Dual Shunt FOC SH Motor with PLL control Application Template</h2>
	<p>	This template generates a code example that exercises Dual Shunt 
	FOC SH Motor with PLL control with the following MHC options:</p>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Implementation: STATIC</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Mode: Interrupt</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Warmup Clock: ADCHS_WARMUP_CLOCK_32</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Interrupt Source: ADC1_DATA0</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Interrupt Vector: ADC1_DATA0</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Driver Number of ADC Channels: 3</br>
	<br><b>&nbsp&nbsp - Channel 0 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - ADC instance: SAR0</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Alternate Input: ADCHS_ALTERNATE_1_CLASS1_AN3</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Trigger Source: ADCHS_TRIGGER_SOURCE_PWM1</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>
	<br><b>&nbsp&nbsp - Channel 1 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - ADC instance: SAR4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Alternate Input: ADCHS_ALTERNATE_3_CLASS1_AN0a</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Trigger Source: ADCHS_TRIGGER_SOURCE_PWM1</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>
	<br><b>&nbsp&nbsp - Channel 2 Setup</b></br>
	<br>&nbsp&nbsp&nbsp&nbsp - ADC instance: SAR7</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Clock Divider: 4</br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>	
	<br>&nbsp&nbsp&nbsp&nbsp - Inputs (class-2): ADCHS_CLASS2_AN10, ADCHS_CLASS2_AN15 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Triggers: PWM1 </br>
	<br>&nbsp&nbsp&nbsp&nbsp - Sample Time Count: 2</br>
	<p>All other ADC and PWM driver configuration options are set to their 
	default values. 
	<p>The ADC driver configuration may be modified by 
	the user using MHC, under Harmony Framework Configuration -> Drivers - > ADC</p>
	<p>The PWM driver configuration may be modified by 
	the user using MHC, under Harmony Framework Configuration -> Drivers - > PWM</p></html>
	---endhelp---
	
ifblock DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}

add "^#include \"/utilities/mhc/config/gencode/framework/motor_control/templates/motor_control_ds_foc_sh_pll_int_opamp_macros_app.h.ftl\">" to list APP_FREEMARKER_MACROS
add "^#include \"/utilities/mhc/config/gencode/framework/motor_control/templates/motor_control_ds_foc_sh_pll_int_opamp_macros_app.c.ftl\">" to list APP_FREEMARKER_MACROS
add "^#include \"/utilities/mhc/config/gencode/framework/motor_control/templates/motor_control_ds_foc_sh_pll_int_opamp_macros_system_config.h.ftl\">" to list APP_FREEMARKER_MACROS

endif

ifblock DUAL_SHUNT_FOC_SH_PLL_INT_OPAMP${INSTANCE}

add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_h_includes/>" to list APP${INSTANCE}_H_INCLUDES
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_system_config_h_app_constants/>" to list APP${INSTANCE}_H_CONSTANTS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_h_type_definitions/>" to list APP${INSTANCE}_H_TYPE_DEFINITIONS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_h_data/>" to list APP${INSTANCE}_H_APP_DATA
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_h_callback_function_declarations/>" to list APP${INSTANCE}_H_APP_CALLBACK_FUNCTION_DECLARATIONS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_h_function_declarations/>" to list APP${INSTANCE}_H_APP_FUNCTION_DECLARATIONS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_h_states/>" to list APP${INSTANCE}_H_APP_STATES

add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_includes/>" to list APP${INSTANCE}_C_INCLUDES
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_global_data/>" to list APP${INSTANCE}_C_GLOBAL_DATA
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_callback_functions/>" to list APP${INSTANCE}_C_CALLBACK_FUNCTIONS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_local_functions/>" to list APP${INSTANCE}_C_LOCAL_FUNCTIONS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_initialize/>" to list APP${INSTANCE}_C_INITIALIZE
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_tasks_data/>" to list APP${INSTANCE}_C_TASKS_DATA
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_tasks_state_init/>" to list APP${INSTANCE}_C_TASKS_STATE_INIT
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_tasks_calls_after_init/>" to list APP${INSTANCE}_C_TASKS_CALLS_AFTER_INIT
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_tasks_state_service_tasks/>" to list APP${INSTANCE}_C_TASKS_STATE_SERVICE_TASKS
add "^@macro_motor_control_ds_foc_sh_pll_int_opamp_app_c_tasks_states/>" to list APP${INSTANCE}_C_TASKS_STATES
endif

ifblock DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}

add "^#include \"/utilities/mhc/config/gencode/framework/motor_control/templates/motor_control_ds_foc_sh_pll_ext_opamp_macros_app.h.ftl\">" to list APP_FREEMARKER_MACROS
add "^#include \"/utilities/mhc/config/gencode/framework/motor_control/templates/motor_control_ds_foc_sh_pll_ext_opamp_macros_app.c.ftl\">" to list APP_FREEMARKER_MACROS
add "^#include \"/utilities/mhc/config/gencode/framework/motor_control/templates/motor_control_ds_foc_sh_pll_ext_opamp_macros_system_config.h.ftl\">" to list APP_FREEMARKER_MACROS

endif

ifblock DUAL_SHUNT_FOC_SH_PLL_EXT_OPAMP${INSTANCE}

add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_h_includes/>" to list APP${INSTANCE}_H_INCLUDES
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_system_config_h_app_constants/>" to list APP${INSTANCE}_H_CONSTANTS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_h_type_definitions/>" to list APP${INSTANCE}_H_TYPE_DEFINITIONS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_h_data/>" to list APP${INSTANCE}_H_APP_DATA
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_h_callback_function_declarations/>" to list APP${INSTANCE}_H_APP_CALLBACK_FUNCTION_DECLARATIONS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_h_function_declarations/>" to list APP${INSTANCE}_H_APP_FUNCTION_DECLARATIONS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_h_states/>" to list APP${INSTANCE}_H_APP_STATES

add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_includes/>" to list APP${INSTANCE}_C_INCLUDES
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_global_data/>" to list APP${INSTANCE}_C_GLOBAL_DATA
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_callback_functions/>" to list APP${INSTANCE}_C_CALLBACK_FUNCTIONS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_local_functions/>" to list APP${INSTANCE}_C_LOCAL_FUNCTIONS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_initialize/>" to list APP${INSTANCE}_C_INITIALIZE
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_tasks_data/>" to list APP${INSTANCE}_C_TASKS_DATA
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_tasks_state_init/>" to list APP${INSTANCE}_C_TASKS_STATE_INIT
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_tasks_calls_after_init/>" to list APP${INSTANCE}_C_TASKS_CALLS_AFTER_INIT
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_tasks_state_service_tasks/>" to list APP${INSTANCE}_C_TASKS_STATE_SERVICE_TASKS
add "^@macro_motor_control_ds_foc_sh_pll_ext_opamp_app_c_tasks_states/>" to list APP${INSTANCE}_C_TASKS_STATES
endif

endmenu
