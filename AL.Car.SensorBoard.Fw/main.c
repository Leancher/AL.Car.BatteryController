/*
 * Car sensor board
 *
 * Created: 15.08.2016 13:43:34
 * Author : Andrew
 */ 

#define DEV_NAME "Car sensor board 1.0"

#include "board/board.h"
#include "libs/dht22.h"
#include "libs/bwl_adc.h"
#include "libs/bwl_uart.h"
#include "libs/bwl_strings.h"
#include "libs/ds18b20_avr.h"
//#include "libs/bwl_simplserial.h"

typedef enum
{
	//Устройство включено
	START_DEVICE = 1,
	//Двигатель запущен
	ENGINE_RUNNING = 2,
	//Двигатель не запущен, зажигание включено
	IGNITION_ON = 3,
	//Зажигание выключено, питание аксессуаров через реле
	POWER_SUPPLY_ON = 4,
	//Зажигание включено, низкий заряд батареи
	BATTERY_LOW_CHARGE = 5,
} DEVICE_STATE;

DEVICE_STATE _current_state=START_DEVICE;

#define DURATION_WORK 1000

#define VOLTAGE_ENGINE_RUNNING 11
#define VOLTAGE_BATTERY_NORMAL_CHARGE 11
#define VOLTAGE_BATTERY_LOW_CHARGE 10

#define ADC_VOLT_MULTIPLIER_MV		(68+2.2)/2.2 * 1.1

int _work_counter = 0;

float _voltage_battery = 0;

float	_climate_humidity_0 = 0;
float	_climate_temperature_0 = 0;
	
void get_battery_voltage()
{
	adc_init(ADCH5, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
	uint16_t val=adc_read_average(3);
	_voltage_battery = val*ADC_VOLT_MULTIPLIER_MV / 1000;
}

void show_voltage_on_display(int _duration)
{
	string_clear(); //Передает битовый ноль, которые не кодирует символы
	string_add_string("Voltage battery = ");
	string_add_float(_voltage_battery,2);
	string_add_string("\r"); //Символ означает, что строка закончилась
	uart_send_string(1,string_buffer);
	var_delay_ms (_duration);
}

void show_temperature_on_display(int _duration)
{
	string_clear(); //Передает битовый ноль, которые не кодирует символы
	string_add_string("Temp = ");
	string_add_float(ds18b20_get_temperature_float(),1);
	string_add_string("\r"); //Символ означает, что строка закончилась
	uart_send_string(1,string_buffer);
	var_delay_ms (_duration);
}

void show_humidity_on_display(int _duration)
{
	string_clear(); //Передает битовый ноль, которые не кодирует символы
	dht22_read(&_climate_temperature_0,&_climate_humidity_0);
	string_add_string("Hum = ");
	string_add_float(_climate_humidity_0,1);
	string_add_string("\r"); //Символ означает, что строка закончилась
	uart_send_string(1,string_buffer);
	var_delay_ms (_duration);
}

void show_data_on_display(char *data)
{
	//uart_send_string(1,"\r\r\r"); //Полная очистка
	
	string_clear();
	string_add_string(data);
	string_add_string("\r"); //Символ означает, что строка закончилась
	uart_send_string(1,string_buffer);
	_delay_ms(1000);
}

void set_state_accessories(byte state)
{
	relay_power_supply_set(state);
}

int main(void)
{
	wdt_enable(WDTO_8S);	

	uart_init_withdivider(1,UBRR_VALUE);
	_delay_ms(1000);

	show_data_on_display("\r\r\r");

	show_data_on_display(DEV_NAME);
	_delay_ms(500);
	
	button_power_supply_enable();

    while (1) 
    {	
		get_battery_voltage();

		show_voltage_on_display(2000);
set_state_accessories(1);

		if (_voltage_battery > VOLTAGE_BATTERY_NORMAL_CHARGE) 
		{
			set_state_accessories(1);
			_work_counter++;
		}
		if (_voltage_battery > VOLTAGE_ENGINE_RUNNING)
		{
			set_state_accessories(1);
			_work_counter=0;
		}
		if (_voltage_battery < VOLTAGE_BATTERY_LOW_CHARGE)
		{
			_work_counter=DURATION_WORK;
		}
		
// 		if (_work_counter >= DURATION_WORK)
// 		{
// 			set_state_accessories(0);
// 			show_data_on_display("Battery low charge");
// 		}
		
		show_temperature_on_display(1000);
		show_humidity_on_display(1000);
		wdt_reset();		
    }
}


