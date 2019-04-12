/*
 * tcc.c
 *
 * Created: 4/10/2019 2:03:25 PM
 *  Author: aleca
 */ 

#include "tcc.h"
#include "coaster_config/coaster_config.h"

void config_pwm(void) {
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	
	pin_conf.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(RGB_BLUE_PIN, &pin_conf);
	
	// set up pwm for blue rgb
	struct tcc_config config_tcc0;
	tcc_get_config_defaults(&config_tcc0, TCC0);
	
	config_tcc0.run_in_standby = true;
	config_tcc0.counter.clock_source =		GCLK_GENERATOR_1;			// 32k clock
	config_tcc0.counter.clock_prescaler =	TCC_CLOCK_PRESCALER_DIV1;	// 32k
	config_tcc0.counter.period =				320;						// 10ms period
	config_tcc0.compare.wave_generation =	TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc0.compare.match[1] =			160;							// 50% duty cycle
	
	// blue
	config_tcc0.pins.enable_wave_out_pin[1] =	true;
	config_tcc0.pins.wave_out_pin[1] =			PIN_PA05E_TCC0_WO1;
	config_tcc0.pins.wave_out_pin_mux[1] =		MUX_PA05E_TCC0_WO1;
	
	
	
	
	// set up pwm for green and red rgb
	struct tcc_config config_tcc1;
	tcc_get_config_defaults(&config_tcc1, TCC1);
	
	config_tcc1.run_in_standby = true;
	config_tcc1.counter.clock_source =		GCLK_GENERATOR_1;			// 32k clock
	config_tcc1.counter.clock_prescaler =	TCC_CLOCK_PRESCALER_DIV1;	// 32k
	config_tcc1.counter.period =			320;						// 10ms period
	config_tcc1.compare.wave_generation =	TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc1.compare.match[0] =			160;							// 50% duty cycle
	config_tcc1.compare.match[1] =			160;							// 50% duty cycle
	
	// green
	config_tcc1.pins.enable_wave_out_pin[0] =	true;
	config_tcc1.pins.wave_out_pin[0] =			PIN_PA06E_TCC1_WO0;
	config_tcc1.pins.wave_out_pin_mux[0] =		MUX_PA06E_TCC1_WO0;
	
	// red
	config_tcc1.pins.enable_wave_out_pin[1] =	true;
	config_tcc1.pins.wave_out_pin[1] =			PIN_PA07E_TCC1_WO1;
	config_tcc1.pins.wave_out_pin_mux[1] =		MUX_PA07E_TCC1_WO1;
	
	tcc_init(&tcc0_instance, TCC0, &config_tcc0);
	tcc_init(&tcc1_instance, TCC1, &config_tcc1);

	tcc_enable(&tcc0_instance);
	tcc_enable(&tcc1_instance);
}