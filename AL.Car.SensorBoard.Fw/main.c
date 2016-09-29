/*
 * AL.Car.SensorBoard.Fw
 *
 * Created: 28.07.2016 8:44:04
 * Author : Andrew
 */ 

#include <avr/io.h>
#include "board/board.h"
#include "modules/display.h"
#include "modules/voltage_data.h"

#define DEV_NAME "Car sensor board 1.0"

#define DURATION_WORK 100

#define VOLTAGE_ENGINE_RUNNING 13.5
#define VOLTAGE_BATTERY_NORMAL_CHARGE 12.5
#define VOLTAGE_BATTERY_LOW_CHARGE 11.8

int _counter_work = 0;
byte _state_heat = 0;

void power_unit_enable()
{
	relay_power_supply_set(1);
	_delay_ms(2000);
	show_data_on_display("\r\r\r");
	show_data_on_display(DEV_NAME);
}

void switch_state_heat_glass(byte _state)
{
	if (_state==1)
	{
		relay_heat_glass_state(1);
		indicator_heat_glass(1);
		return;
	}
	if (_state==0)
	{
		relay_heat_glass_state(0);
		indicator_heat_glass(0);
	}
}

int get_state_heat_glass_button()
{
	static int index=0;
	if (index>5)
	{
		index=0;
		if (button_heat_glass_is_pressed()==1) return 1;
	}
	index++;
	return 2;
}

// void set_state_heat_glass()
// {
// 	static int _counter_work = 0;
// 
// 	if (button_heat_glass_is_pressed()==1)
// 	{
// 		if (_state_heat==0)
// 		{
// 			_state_heat=1;
// 			switch_state_heat_glass(1);
// 		}
// 		else
// 		{
// 			_state_heat=0;
// 			switch_state_heat_glass(0);
// 		}
// 		_counter_work=0;
// 	}
// 	if (_state_heat==1) _counter_work++;
// 	if (_counter_work>200)
// 	{
// 		_state_heat=0;
// 		_counter_work=0;
// 		switch_state_heat_glass(0);
// 	}
// }

void set_current_state()
{
	float _voltage_battery = 0;
	_voltage_battery = get_battery_voltage();
	if (_voltage_battery > VOLTAGE_ENGINE_RUNNING)
	{
		relay_power_supply_set(1);
		_counter_work=1;
	}

	show_all_data_on_display(20);
	_counter_work++;
	//Задержка для исключений временного изменения напряженя
	if (_counter_work < 5) return;

	if (_counter_work>DURATION_WORK)
	{
		relay_power_supply_set(0);
		_counter_work=0;
	}
	if (_voltage_battery<VOLTAGE_BATTERY_LOW_CHARGE)
	{
		show_data_on_display("Battery low charge");
		relay_power_supply_set(0);
		_counter_work=0;
	}	
	if (button_power_supply_is_pressed()==1)
	{
		relay_power_supply_set(0);
		_counter_work=0;
	}
}

int main(void)
{
	uart_init_withdivider(1,UBRR_VALUE);
	power_unit_enable();

	button_power_supply_enable();
	//button_heat_glass_enable();

    while (1) 
    {
		set_current_state();
		_delay_ms(100);
    }
}