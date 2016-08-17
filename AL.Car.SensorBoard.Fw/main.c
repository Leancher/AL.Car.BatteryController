/*
 * MeteoSensor.c
 *
 * Created: 02.07.2016 13:43:34
 * Author : bessgusev
 */ 

#define DEV_NAME "Car sensor board 1.0      "

#include "board/board.h"
//#include "libs/dht22.h"
#include "libs/bwl_adc.h"
#include "libs/bwl_uart.h"
#include "libs/bwl_strings.h"
//#include "libs/bwl_simplserial.h"

#define ADC_VOLT_MULTIPLIER_MV		(68+2.2)/2.2 * 1.1

float	climate_humidity_0 = 0;
float	climate_temperature_0 = 0;
char	buf[2] = "";
float	temp, press = 0;
char	pulse_counter = 0;

//void sserial_send_start(){}

//void sserial_send_end(){}

// void sserial_process_request()
// {
// 	//чтение температуры и влажности DHT
// 	if (sserial_request.command==1)
// 	{
// 		dht22_read(&climate_temperature_0, &climate_humidity_0);
// 		sserial_response.result=0;
// 		sserial_response.datalength=4;
// 		uint16_t temp0_int=(uint16_t)(climate_temperature_0*10.0+1000.0);
// 		sserial_response.data[0] = temp0_int>>8;
// 		sserial_response.data[1] = temp0_int&0xFF;
// 	    temp0_int=(uint16_t)(climate_humidity_0*10.0+1000.0);
// 		sserial_response.data[2] = temp0_int>>8;
// 		sserial_response.data[3] = temp0_int&0xFF;			
// 		sserial_send_response();
// 	}
// 
// 	//чтение текущих значений датчика освещенности
// 	if (sserial_request.command==7)
// 	{
// 		sserial_response.result=0;
// 		sserial_response.datalength=4;
// 		int val = adc_read_average(5);
// 		sserial_response.data[0] = 0;//val>>24;
// 		sserial_response.data[1] = 0;//val>>16;
// 		sserial_response.data[2] = val>>8;
// 		sserial_response.data[3] = val&0xFF;
// 		sserial_send_response();
// 	}
// }
	
int get_acc_voltage()
{
	adc_init(ADCH5, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
	uint16_t val=adc_read_average(3);
	uint16_t result=val*ADC_VOLT_MULTIPLIER_MV;
	return result;
}

int main(void)
{
	wdt_enable(WDTO_8S);	

	uart_init_withdivider(1,UBRR_VALUE);
	_delay_ms(1500);
	string_clear();
	string_add_string("Car sensor board");
	string_add_crlf();
	uart_send_string(1,string_buffer);
	_delay_ms(1000);

	
    while (1) 
    {	
		string_clear();
		string_add_int(get_acc_voltage());
		string_add_crlf();
		uart_send_string(1,string_buffer);
		_delay_ms(1000);
		wdt_reset();		
    }
}


