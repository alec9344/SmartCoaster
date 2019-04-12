/*
 * adc.h
 *
 * Created: 3/13/2019 2:26:40 PM
 *  Author: aleca
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <asf.h>
#include "coaster_config.h"

// Initialize ADC input on PB02, PA08, and PA05
void configure_adc(void);

// Get ADC reading from specified ADC pin
uint16_t read_adc(const enum adc_positive_input pin);


#endif /* ADC_H_ */