/*
 * coaster_app.c
 *
 * Created: 4/3/2019 4:32:52 PM
 *  Author: aleca
 */ 

#include "coaster_app.h"
#include "adc/adc.h"

// get current weight on coaster
uint16_t get_weight(void) {
	return 4095-read_adc(FORCE_SENSOR_ADC_POSITIVE_INPUT);
}

// calibrate (get new empty cup weight)
void calibrate_new_cup(void) {
	// Make RGB LED yellow to indicate waiting for no cup calibration
	set_rgb_led(320,320,0);
	
	// wait for button press
	while(port_pin_get_input_level(BUTTON_PIN) == false);
	delay_ms(10); // wait for bouncing
	while(port_pin_get_input_level(BUTTON_PIN) == true);
	delay_ms(10); // wait for bouncing
	
	// set no cup weight
	no_cup_weight = get_weight();
	
	// blink LED green to indicate success
	set_rgb_led(0,320,0);
	delay_ms(500);
	
	// Make RGB LED orange to indicate waiting for empty cup calibration
	set_rgb_led(320,160,0);
	
	// wait for button press
	while(port_pin_get_input_level(BUTTON_PIN) == false);
	delay_ms(10); // wait for bouncing
	while(port_pin_get_input_level(BUTTON_PIN) == true);
	delay_ms(10); // wait for bouncing
	
	// set empty cup weight
	empty_cup_weight = get_weight();
	
	// blink LED green to indicate success
	set_rgb_led(0,320,0);
	delay_ms(500);
	
	// Make RGB LED red to indicate waiting for full cup calibration
	set_rgb_led(320,0,0);
	
	// wait for button press
	while(port_pin_get_input_level(BUTTON_PIN) == false);
	delay_ms(10); // wait for bouncing
	while(port_pin_get_input_level(BUTTON_PIN) == true);
	delay_ms(10); // wait for bouncing
	
	// set full cup weight
	full_cup_weight = get_weight();
	
	// blink LED green to indicate success
	set_rgb_led(0,320,0);
	delay_ms(500);
	
	// turn off rgb led
	set_rgb_led(0,0,0);
}

void set_rgb_led(uint16_t r, uint16_t g, uint16_t b) {
	tcc_set_compare_value(&tcc1_instance, 1, r);
	tcc_set_compare_value(&tcc1_instance, 0, g);
	tcc_set_compare_value(&tcc0_instance, 1, b);
}

// get cup weight status
weight_status_t get_cup_weight_status(void) {
	// get the weight of the cup
	force_adc_val = get_weight();
	
	// no cup on coaster
	if (force_adc_val < (no_cup_weight+(empty_cup_weight-no_cup_weight)/4)) {
		return NO_CUP;
	}
	
	// get the range from empty to full cup weight
	uint16_t range = full_cup_weight - empty_cup_weight;
	
	// if cup is less than 1/8th full, call it empty
	if (force_adc_val < (empty_cup_weight + range/8)) {
		return EMPTY_CUP;
	}
	
	// if adc read greater than empty cup val by less than 1/2 the range, call it quarter full
	if (force_adc_val < (empty_cup_weight + range/2)) {
		return QUARTER_CUP;
	}
	
	// if adc read greater than empty cup val by less than 15/19 the range, call it half full
	if (force_adc_val < (empty_cup_weight + 15*range/19)) {
		return HALF_CUP;
	}
	
	// if adc read greater than empty cup val by less than 35/38 the range, call it 3/4 full
	if (force_adc_val < (empty_cup_weight + 35*range/38)) {
		return THREEQUARTER_CUP;
	}
	
	// cup is full
	return FULL_CUP;
}