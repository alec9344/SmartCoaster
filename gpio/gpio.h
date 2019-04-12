/*
 * gpio.h
 *
 * Created: 3/20/2019 4:51:45 PM
 *  Author: aleca
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "config/coaster_config.h"

// Configure GPIO pins
void gpio_config(void);

// Set up external interrupts for push buttons
void extint_config(void);

// Configure callbacks for push button interrupts
void extint_config_callbacks(void);

// Calls functions for external interrupt configuration
void extint_setup(void);

// Callback for increase temperature button
void button_callback(void);

#endif /* GPIO_H_ */