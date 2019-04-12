/*
 * tc.c
 *
 * Created: 3/13/2019 3:52:48 PM
 *  Author: aleca
 */ 

#include "tc.h"
#include "coaster_app/coaster_app.h"
#include "ftoa/ftoa.h"

void configure_tc(void)
{
	//! [setup_config]
	struct tc_config config_tc;
	//! [setup_config]
	//! [setup_config_defaults]
	tc_get_config_defaults(&config_tc);
	//! [setup_config_defaults]

	//! [setup_change_config]
	config_tc.counter_size = TC_COUNTER_SIZE_16BIT;
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_16_bit.compare_capture_channel[0] = 32;	// approximately 1s (1s*32k/1024 ~= 32)
	config_tc.run_in_standby = true;
	//! [setup_change_config]

	//! [setup_set_config]
	tc_init(&tc_instance, TC3, &config_tc);
	//! [setup_set_config]

	//! [setup_enable]
	tc_enable(&tc_instance);
	//! [setup_enable]
}

void configure_tc_callbacks(void)
{
	//! [setup_register_callback]
	tc_register_callback(&tc_instance, tc_callback, TC_CALLBACK_CC_CHANNEL0);

	//! [setup_enable_callback]
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
	//! [setup_enable_callback]
}

void tc_callback(struct tc_module *const module_inst)
{
	adc_enable(&adc_instance);
	usart_enable(&usart_instance);
	weight_status_t w_status = get_cup_weight_status();
	if (w_status == NO_CUP) {
		// TODO: do something with LED
		printf("NO CUP!\r\n");
	}
	else if (w_status == EMPTY_CUP) {
		// TODO: do something with LED
		printf("CUP IS EMPTY!\r\n");
	}
	else if (w_status == QUARTER_CUP) {
		// TODO: do something with LED
		printf("CUP IS A QUARTER FULL!\r\n");
	}
	else if (w_status == HALF_CUP) {
		// TODO: do something with LED
		printf("CUP IS HALF FULL!\r\n");
	}
	else if (w_status == THREEQUARTER_CUP) {
		// TODO: do something with LED
		printf("CUP IS THREE QUARTERS FULL!\r\n");
	}
	else {
		// TODO: do something with LED
		printf("CUP IS FULL!\r\n");
	}
	intToStr(force_adc_val,str,1);
	printf("ADC value: %s\r\n\r\n", str);
	tc_set_count_value(&tc_instance, 0);
}