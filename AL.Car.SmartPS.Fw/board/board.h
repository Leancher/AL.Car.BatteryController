#ifndef BOARD_H
#define BOARD_H

#define F_CPU 4000000UL
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//#include <util/setbaud.h>

#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

//User Libraries
//#include "../libs/bwl_uart.h"
#include "../libs/bwl_adc.h"

typedef unsigned char byte;

void var_delay_ms(int ms);

void adc_init_voltage_acc();
void adc_init_voltage_battery();
void adc_init_voltage_power_in();
void adc_init_voltage_generator();

void led_red_set(byte state);
void led_yellow_set(byte state);
void led_green_set(byte state);

void relay_battery_charge(byte state);
void relay_battery_power(byte state);
void relay_power_add_device(byte state);
void relay_usb(byte state);

#endif /* BOARD_H_ */