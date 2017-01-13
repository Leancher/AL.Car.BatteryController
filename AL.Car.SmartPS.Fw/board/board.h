#ifndef BOARD_H
#define BOARD_H

#define F_CPU 8000000UL
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <util/setbaud.h>

#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

//User Libraries
#include "../libs/bwl_uart.h"
#include "../libs/bwl_adc.h"

typedef unsigned char byte;

void var_delay_ms(int ms);

void adc_init_voltage_input();
void adc_init_voltage_battery();

void button_power_supply_enable();
byte button_power_supply_is_pressed();
void relay_power_supply_set(byte state);
void relay_charge_battery(byte state);

void led_red_set(byte state);
void led_yellow_set(byte state);
void led_green_set(byte state);

void alarm_activate_in_enable();
byte alarm_activate_in_is_pressed();

void button_car_alarm_enable();
byte button_car_alarm_is_pressed();

#endif /* BOARD_H_ */