/*
 * AL.Car.SmartPS.Fw
 *
 * Created: 28.07.2016 8:44:04
 * Author : Andrew
 */ 

#include <avr/io.h>
#include "board/board.h"

#define DEV_NAME "SmartPS board 1.0"
#define ADC_VOLT_MULTIPLIER_MV		(68+2.2)/2.2 * 1.1
#define DELAY_BEFOR_CONNECT 100 //10 000 мс / 100 циклов


#define DURATION_WORK 600

#define VOLTAGE_ENGINE_RUN 13000
#define VOLTAGE_BATTERY_NORMAL_CHARGE 12.5
#define VOLTAGE_BATTERY_LOW_CHARGE 11.8

typedef enum
{
	BATTERY_DISCHARGE=1,
	BATTERY_CHARGE=2,
} DEVICE_STATE;
DEVICE_STATE current_state = BATTERY_DISCHARGE;

int counter = 0;

int get_voltage()
{
	uint16_t val=0;
	val=adc_read_average(10);
	val=val*ADC_VOLT_MULTIPLIER_MV;
	return val;
}

void device_init()
{
	relay_add_battery(0);
	button_power_supply_enable();
	button_car_alarm_enable();	
}

int main(void)
{
	wdt_enable(WDTO_8S);
	//uart_init_withdivider(1,UBRR_VALUE);
		
	adc_init_voltage_acc();
	led_yellow_set(1);
	
    while (1) 
    {
		wdt_reset();
		if (get_voltage()>VOLTAGE_ENGINE_RUN)
		{
			if (current_state==BATTERY_DISCHARGE)
			{
				counter++;
				if (counter>DELAY_BEFOR_CONNECT)
				{
					current_state=BATTERY_CHARGE;
					relay_add_battery(1);
					led_green_set(1);
					counter=0;
				}			
			}

		}
		else
		{
			current_state=BATTERY_DISCHARGE;
			relay_add_battery(0);
			led_green_set(0);
			counter=0;
		}
		_delay_ms(100);
    }
}