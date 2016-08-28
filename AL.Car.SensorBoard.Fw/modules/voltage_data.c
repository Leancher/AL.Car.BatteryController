#include <avr/io.h>
#include "voltage_data.h"
#include "..\libs\bwl_adc.h"

float get_battery_voltage()
{
	adc_init(ADCH6, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
	uint16_t val=adc_read_average(3);
	return val*ADC_VOLT_MULTIPLIER_MV / 1000 - 0.4;
}
