#ifndef BOARD_H
#define BOARD_H

#define F_CPU 8000000UL
#define BAUD 9600

#define UART_DISPLAY 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <util/setbaud.h>

#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

typedef unsigned char byte;

void var_delay_ms(int ms);
void button_power_supply_enable();
byte button_power_supply_is_pressed();
void relay_power_supply_set(byte _state);
void alarm_activate_in_enable();
byte alarm_activate_in_is_pressed();

#endif /* BOARD_H_ */