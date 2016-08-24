#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

//Кнопка поддержки питания активация
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