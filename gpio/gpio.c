/*
 * gpio.c
 *
 * Created: 3/20/2019 4:51:59 PM
 *  Author: aleca
 */ 

#include "gpio.h"
#include "coaster_app/coaster_app.h"
#include "tcc/tcc.h"

void gpio_config(void) {
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	
	// configure LED as output
	pin_conf.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_PIN, &pin_conf);
}

void extint_config(void) {
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	
	// Configure push button as input
	pin_conf.direction = PORT_PIN_DIR_INPUT;
	pin_conf.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_PIN, &pin_conf);
	
	// Configure button interrupt
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	
	// button for increasing temperature threshold
	config_extint_chan.gpio_pin				= BUTTON_EIC_PIN;
	config_extint_chan.gpio_pin_mux			= BUTTON_EIC_MUX;
	config_extint_chan.gpio_pin_pull		= BUTTON_EIC_PULL;
	config_extint_chan.detection_criteria	= BUTTON_EIC_EDGE;
	config_extint_chan.wake_if_sleeping		= true;
	extint_chan_set_config(BUTTON_EIC_LINE, &config_extint_chan);
}

void extint_config_callbacks(void)
{
	extint_register_callback(button_callback, BUTTON_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	
	extint_chan_enable_callback(BUTTON_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
}

void extint_setup(void) {
	extint_config();
	extint_config_callbacks();
}

void button_callback(void) {
	// disable interrupts
	system_interrupt_disable_global();
	
	// wait for bouncing
	delay_ms(10); 
	
	// check if button remains held for about 5 seconds (would indicate new cup calibration)
	int press_dur = 0;
	while (port_pin_get_input_level(BUTTON_PIN) == false) {
		delay_ms(1);
		press_dur++;
		if (press_dur == 3000) break;
	}
	
	// if button was held for a about 5 seconds, blink it rapidly 10 times
	if (press_dur == 3000) {
		// enable adc
		adc_enable(&adc_instance);
		
		// calibrate
		calibrate_new_cup();
		for (int i = 0; i < 10; i++) {
			port_pin_set_output_level(LED_PIN, true);
			delay_ms(50);
			port_pin_set_output_level(LED_PIN, false);
			delay_ms(50);
		}
	}
	
	// if button was pressed and not held, change temperature setting
	// and blink LED to indicate temperature setting
	else {
		// there are only 5 temperature levels (0-4)
 		temperature_threshold = temperature_threshold == 4 ? 0 : temperature_threshold+1;
 		for (int i = 0; i < temperature_threshold+1; i++) {
 			port_pin_set_output_level(LED_PIN, true);
 			delay_ms(125);
 			port_pin_set_output_level(LED_PIN, false);
 			delay_ms(125);
 		}
	}
	
	//adc_val = read_adc(TEMP_SENSOR_ADC_POSITIVE_INPUT);
	
	// wait for button to be released
	while(port_pin_get_input_level(BUTTON_PIN) == 0); 
	
	// clear interrupt flag
	EIC->INTFLAG.bit.EXTINT10 = 1; 
	
	// enable interrupts before exiting
	system_interrupt_enable_global();
}
