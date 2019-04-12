/*
 * coaster_config.h
 *
 * Created: 3/13/2019 2:43:07 PM
 *  Author: aleca
 */ 

#include <asf.h>

#ifndef COASTER_CONFIG_H_
#define COASTER_CONFIG_H_

// force sensor
#define FORCE_SENSOR_ADC_POSITIVE_INPUT ADC_POSITIVE_INPUT_PIN8
#define FORCE_SENSOR_ADC_PIN PIN_PB00

// temperature sensor
#define TEMP_SENSOR_ADC_POSITIVE_INPUT ADC_POSITIVE_INPUT_PIN9
#define TEMP_SENSOR_ADC_PIN PIN_PB01

// LED gpio pin
#define LED_PIN PIN_PA08

// RGB LED gpio pins
#define RGB_BLUE_PIN	PIN_PA05
#define RGB_GREEN_PIN	PIN_PA06
#define RGB_RED_PIN		PIN_PA07

// button gpio pin
#define BUTTON_PIN PIN_PA10

// button extint pin
#define BUTTON_EIC_PIN PIN_PA10A_EIC_EXTINT10

// button extint muxe
#define BUTTON_EIC_MUX MUX_PA10A_EIC_EXTINT10

// button extint pulls
#define BUTTON_EIC_PULL EXTINT_PULL_UP

// button extint edge detection
#define BUTTON_EIC_EDGE EXTINT_DETECT_FALLING

// button extint lines
#define BUTTON_EIC_LINE 10

// global variables for coaster application
uint16_t force_adc_val, temp_adc_val;
char str[10];
uint8_t temperature_threshold;	// Temperature threshold for buzzer/led to turn on
uint16_t no_cup_weight;			// No cup weight (raw adc value)
uint16_t empty_cup_weight;		// Empty cup weight (raw adc value) for calibrated cup
uint16_t full_cup_weight;		// Full cup weight (taw adc value) for calibrated cup

// TC instances
struct tc_module tc_instance;

// ADC instances
struct adc_module adc_instance;

// TCC instances
struct tcc_module tcc0_instance;
struct tcc_module tcc1_instance;

// USART instances
struct usart_module usart_instance;

#endif /* COASTER_CONFIG_H_ */