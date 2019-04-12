/*
 * coaster_app.h
 *
 * Created: 4/3/2019 4:32:41 PM
 *  Author: aleca
 */ 

#ifndef COASTER_APP_H_
#define COASTER_APP_H_

#include <asf.h>

enum weight_status {
	NO_CUP, EMPTY_CUP, QUARTER_CUP, HALF_CUP, THREEQUARTER_CUP, FULL_CUP	
};

typedef enum weight_status weight_status_t;

// get current weight on coaster
uint16_t get_weight(void);

// calibrate (get new empty cup weight)
void calibrate_new_cup(void);

// set rgb led (each value between 0-320)
void set_rgb_led(uint16_t r, uint16_t g, uint16_t b);

// get cup weight status
weight_status_t get_cup_weight_status(void);

// get cup temperature status



#endif /* COASTER_APP_H_ */