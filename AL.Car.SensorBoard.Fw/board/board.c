#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

void button_car_alarm_enable()
{
	setbit(DDRB,2,0);
	setbit(PORTB,2,1);
}

byte button_car_alarm_is_pressed()
{
	if (getbit(PINB,2)) {return 0;}
	return 1;
}

//Кнопка поддержки питания - активация
void button_power_supply_enable()
{
	setbit(DDRB,7,0);
	setbit(PORTB,7,1);
}

//Кнопка поддержки питания - получение состояния
byte button_power_supply_is_pressed()
{
	if (getbit(PINB,7)) {return 0;}
	return 1;
}

void button_heat_glass_enable()
{
	setbit(DDRB,4,0);
	setbit(PORTB,4,1);	
}

byte button_heat_glass_is_pressed()
{
	if (getbit(PINB,4)) {return 0;}
	return 1;	
}

void relay_heat_glass_state(byte _state)
{
	setbit(DDRD,4,1);
	setbit(PORTD,4,_state);
}

void indicator_heat_glass (byte state)
{
	
}

void relay_power_supply_set(byte _state)
{
	setbit(DDRD,5,1);
	setbit(PORTD,5,_state);
}

void alarm_activate_in_enable()
{
	setbit(DDRB,2,0);
	setbit(PORTB,2,1);
}

byte alarm_activate_in_is_pressed()
{
	if (getbit(PINB,2)) {return 0;}
	return 1;	
} 