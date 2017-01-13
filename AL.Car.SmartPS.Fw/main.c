/*
 * AL.Car.SmartPS.Fw
 *
 * Created: 28.07.2016 8:44:04
 * Author : Andrew
 */ 

#include <avr/io.h>
#include "board/board.h"

#define DEV_NAME "PS board 1.0"
#define ADC_VOLT_MULTIPLIER_MV		(68+2.2)/2.2 * 1.1
#define DELAY_BEFOR_CONNECT 100 //10 000 мс / 100 циклов

#define VOLTAGE_INPUT_ENGINE_RUN 13000
#define VOLTAGE_INPUT_NORMAL 12500
#define VOLTAGE_BATTERY_DISCHARGEON 12500
#define VOLTAGE_BATTERY_DISCHARGEOFF 11800

typedef enum
{
	BATTERY_DISCHARGED=1,
	BATTERY_CHARGED=2,
	BATTERY_CHARGING=3,
	BATTERY_DISCHARGING=4,
} DEVICE_STATE;
DEVICE_STATE current_state = BATTERY_DISCHARGED;

int counter = 0;

int get_voltage_input()
{
	adc_init_voltage_input();
	int val=0;
	val=adc_read_average(3)*ADC_VOLT_MULTIPLIER_MV;
	return val;
}

int get_voltage_battery()
{
	adc_init_voltage_battery();
	int val=0;
	val=adc_read_average(3)*ADC_VOLT_MULTIPLIER_MV;
	return val;
}

void device_init()
{
	relay_charge_battery(0);
	button_power_supply_enable();
	button_car_alarm_enable();	
}

int main(void)
{
	wdt_enable(WDTO_8S);
	
	led_yellow_set(1);
	
    while (1) 
    {
		wdt_reset();

		if (get_voltage_input()<VOLTAGE_INPUT_NORMAL)
		{
			relay_charge_battery(0);
			led_green_set(0);
			led_yellow_set(0);
			led_red_set(0);
			if (get_voltage_battery()<VOLTAGE_BATTERY_DISCHARGEOFF)
			{
				relay_power_supply_set(0);
			}
		}

		if (get_voltage_input()>VOLTAGE_INPUT_NORMAL)
		{
			if (get_voltage_battery()<VOLTAGE_BATTERY_DISCHARGEOFF)
			{
				led_green_set(0);
				led_yellow_set(0);				
				led_red_set(1);
			}
		}

		if (get_voltage_input()>VOLTAGE_INPUT_ENGINE_RUN)
		{
			relay_power_supply_set(1);
			if (get_voltage_battery()<VOLTAGE_BATTERY_DISCHARGEON)
			{
				relay_charge_battery(1);
				led_green_set(0);
				led_yellow_set(1);
				led_red_set(0);
			}
		}
		if (get_voltage_battery()>VOLTAGE_BATTERY_DISCHARGEON)
		{
			relay_charge_battery(0);
			led_yellow_set(0);
			led_green_set(1);
			led_red_set(0);
		}
		_delay_ms(100);
    }
}