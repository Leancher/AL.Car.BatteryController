#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

void adc_init_voltage_acc()
{
	adc_init(0, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
}

void adc_init_voltage_battery()
{
	adc_init(1, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
}

void adc_init_voltage_power_in()
{
	adc_init(2, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
}

void adc_init_voltage_generator()
{
	adc_init(3, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
}

void led_red_set(byte state)
{
	setbit(DDRB,1,1);
	setbit(PORTB,1,state);	
}

void led_yellow_set(byte state)
{
	setbit(DDRB,2,1);
	setbit(PORTB,2,state);
}

void led_green_set(byte state)
{
	setbit(DDRB,3,1);
	setbit(PORTB,3,state);
}

void relay_battery_charge(byte state)
{
	setbit(DDRB,4,1);
	setbit(PORTB,4,state);
}

void relay_battery_power(byte state)
{
	setbit(DDRB,6,1);
	setbit(PORTB,6,state);
}

void relay_power_add_device(byte state)
{
	setbit(DDRB,7,1);
	setbit(PORTB,7,state);
}

void relay_usb(byte state)
{
	setbit(DDRD,4,1);
	setbit(PORTD,4,state);
}