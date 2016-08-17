#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

#define TEMP_SENSOR_PIN 1
void set_ow_pin(byte mode, byte state)
{
	if (state){PORTC|=1<<TEMP_SENSOR_PIN;	}else{PORTC&=(~(1<<TEMP_SENSOR_PIN));}
	if (mode){DDRC|=1<<TEMP_SENSOR_PIN;	}else{DDRC&=(~(1<<TEMP_SENSOR_PIN));}
}

unsigned char get_ow_pin()
{
	return ((PINC&(1<<TEMP_SENSOR_PIN)));
}

