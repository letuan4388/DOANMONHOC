		#ifndef MYLIBRARY_INCLUDE_H_
#define MYLIBRARY_INCLUDE_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#define LED         GPIO_PIN_0
#define GPIO1       GPIO_PIN_1
#define GPIO2       GPIO_PIN_2
#define SW1         GPIO_PIN_6
#define SW2         GPIO_PIN_7

static int GPIO1_STATE = 0;
static int GPIO2_STATE = 0;

#endif /* MYLIBRARY_INCLUDE_H_ */
