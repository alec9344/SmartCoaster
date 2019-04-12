/*
 * my_adc.c
 *
 * Created: 2/27/2019 3:02:56 PM
 *  Author: jagnese2018
 */ 

#include "adc.h"

void configure_adc(void) {
	// structs for configurations
	struct system_pinmux_config pinmux_conf;
	struct adc_config adc_conf;

	// Get defaults
	system_pinmux_get_config_defaults(&pinmux_conf);
	adc_get_config_defaults(&adc_conf);
	
	// configure analog input pins
	pinmux_conf.input_pull = SYSTEM_PINMUX_PIN_PULL_NONE;
	pinmux_conf.mux_position = 1;
	system_pinmux_pin_set_config(FORCE_SENSOR_ADC_PIN, &pinmux_conf);
	system_pinmux_pin_set_config(TEMP_SENSOR_ADC_PIN, &pinmux_conf);
	
	
	// configure ADC
	adc_conf.clock_source = GCLK_GENERATOR_0;
	adc_conf.reference = ADC_REFCTRL_REFSEL_INTVCC0;
	adc_conf.clock_prescaler = ADC_CTRLB_PRESCALER_DIV4;
	adc_conf.differential_mode = false;
	adc_conf.negative_input = ADC_NEGATIVE_INPUT_GND;
	adc_conf.accumulate_samples = ADC_AVGCTRL_SAMPLENUM_1024;
	adc_conf.divide_result = 0x4;
	adc_conf.resolution = ADC_RESOLUTION_CUSTOM;
	
	// initialize ADC
	adc_init(&adc_instance, ADC, &adc_conf);
	
	// enable ADC
	adc_enable(&adc_instance);
}

uint16_t read_adc(const enum adc_positive_input pin) {
	adc_set_positive_input(&adc_instance, pin);
	ADC->SWTRIG.bit.START = 1;				// start ADC conversion
	while(ADC->INTFLAG.bit.RESRDY == 0);	// wait for result
	uint16_t res = ADC->RESULT.reg;			// read ADC value
	return res;
}
