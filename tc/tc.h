/*
 * tc.h
 *
 * Created: 3/13/2019 3:52:41 PM
 *  Author: aleca
 */ 


#ifndef TC_H_
#define TC_H_

#include <asf.h>
#include "coaster_config/coaster_config.h"

// TC configuration and callbacks
void configure_tc(void);
void configure_tc_callbacks(void);
void tc_callback(struct tc_module *const module_inst);

#endif /* TC_H_ */