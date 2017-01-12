#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

void adc_init_voltage_input()
{
	adc_init(1, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
}

void adc_init_voltage_acc()
{
	adc_init(0, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
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

void led_red_set(byte state)
{
	setbit(DDRB,3,1);
	setbit(PORTB,3,state);	
}

void led_yellow_set(byte state)
{
	setbit(DDRB,4,1);
	setbit(PORTB,4,state);
}

void led_green_set(byte state)
{
	setbit(DDRB,5,1);
	setbit(PORTB,5,state);
}

void relay_add_battery(byte state)
{
	setbit(DDRD,4,1);
	setbit(PORTD,4,state);	
}

void relay_power_supply_set(byte state)
{
	setbit(DDRD,5,1);
	setbit(PORTD,5,state);
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