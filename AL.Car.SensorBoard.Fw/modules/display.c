#include "display.h"

float	_climate_humidity_0 = 0;
float	_climate_temperature_0 = 0;

void show_data_on_display(char *data)
{
	//uart_send_string(1,"\r\r\r"); //Полная очистка
	 
	string_clear();
	string_add_string(data);
	string_add_string("\r"); //Символ означает, что строка закончилась
	uart_send_string(1,string_buffer);
	_delay_ms(1000);
}

void show_voltage_on_display(int _duration)
{
	static int index=0;
	if (index==0)
	{
		string_clear(); //Передает битовый ноль, которые не кодирует символы
		string_add_string("Voltage battery = ");
		string_add_float(get_battery_voltage(),2);
		string_add_string("\r"); //Символ означает, что строка закончилась
		uart_send_string(1,string_buffer);
	}
	index++;
	if (index > _duration) index=0;
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

void show_all_data_on_display(int _duration)
{
	static int _mode=0;
	static int index=0;
	if (index==0)
	{
		string_clear(); //Передает битовый ноль, которые не кодирует символы
		dht22_read(&_climate_temperature_0,&_climate_humidity_0);
		if (_mode==0)
		{
			string_add_string("V = ");
			string_add_float(get_battery_voltage(),2);
			string_move_to_new();
			string_add_string("Tout = ");
			string_add_float(ds18b20_get_temperature_float(),1);
			string_move_to_new();
		}
		if (_mode==1)
		{
			string_add_string("Tin = ");
			string_add_float(_climate_temperature_0,1);
			string_move_to_new();
			string_add_string("Hin = ");
			string_add_float(_climate_humidity_0,1);
			string_move_to_new();
		}
		string_add_string("\r"); //Символ означает, что строка закончилась
		uart_send_string(1,string_buffer);
		_mode++;
		if (_mode>1) _mode=0;
	}
	index++;
	if (index > _duration) index=0;
}