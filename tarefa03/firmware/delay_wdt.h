
#ifndef DELAY_WDT_H_
#define DELAY_WDT_H_

#include <stdint.h>

void init_clock_system();
void config_wd_as_timer();
void delay_wdt(uint16_t ms);


#endif /* DELAY_WDT_H_ */
