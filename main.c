#include <asf.h>
#include "config/coaster_config.h"
#include "coaster_app/coaster_app.h"
#include "adc/adc.h"
#include "tc/tc.h"
#include "ftoa/ftoa.h"
#include "usart/usart.h"
#include "gpio/gpio.h"
#include "tcc/tcc.h"

void init_all(void);

int main (void)
{
	system_init();
	init_all();
	system_interrupt_enable_global();
	
	no_cup_weight = get_weight();
	
	while (1) {
		adc_disable(&adc_instance);
		usart_disable(&usart_instance);
		sleepmgr_enter_sleep();
	}
}

void init_all(void) {
	configure_usart();
	configure_adc();
	configure_tc();
	configure_tc_callbacks();
	sleepmgr_init();
	extint_setup();
	gpio_config();
	config_pwm();
}
