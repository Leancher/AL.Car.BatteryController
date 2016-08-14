#define BAUD 9600

#include "board/board.h"
#include "winstar1602.h"
#include "refs-avr/strings.h"
#include "libs/bwl_uart.h"

#include <util/setbaud.h>

void copy_string_to_line(char line)
{
	if (line==1)
	{
		for (int i=0; i<16; i++)
		{
			lcd_line_1[i]=string_buffer[i];
		}
	}
	if (line==2)
	{
		for (int i=0; i<16; i++)
		{
			lcd_line_2[i]=string_buffer[i];
		}
	}
	

}
// 
// void show_voltage_current(float volt, float current)
// {
// 	string_clear();
// 	string_add_string("Voltage: ");
// 	string_add_float(volt,2);
// 	copy_string_to_line(1);
// 	
// 	string_clear();
// 	string_add_string("Current: ");
// 	string_add_float(current,2);
// 	copy_string_to_line(2);
// 	lcd_writebuffer();
// }
// 
// void show_resistanse(int relay_code)
// {
// 	string_clear();
// 	string_add_string("R = ");
// 	if (relay_code==0)
// 	{
// 		string_add_string("off");
// 	}else
// 	{
// 		string_add_float(relay_get_resistance(relay_code),1);
// 		string_add_string(" Ohm");
// 	}
// 	copy_string_to_line(1);
// 	string_clear();
// 	copy_string_to_line(2);
// 	lcd_writebuffer();
// }
// 
// void show_resistanse_voltage_current(float resistance, float voltage)
// {
// 	string_clear();
// 	string_add_string("R=");
// 	if (resistance<0)
// 	{
// 		string_add_string("off");
// 	}else
// 	{
// 		string_add_float(resistance,1);
// 	}
// 	string_add_string(", U=");
// 	string_add_float(voltage,2);
// 	copy_string_to_line(1);
// 	string_clear();
// 	if (resistance<0)
// 	{
// 		string_add_string("I=0 A, P=0 W");
// 	}else
// 	{
// 		string_add_string("I=");
// 		float curr=voltage/resistance;
// 		string_add_float(curr,2);
// 		
// 		string_add_string(", P=");
// 		float pow=voltage*curr;
// 		string_add_float(pow,2);
// 	}
// 	copy_string_to_line(2);
// 	lcd_writebuffer();
// }

int main(void)
{
	lcd_init();

	uart_init_withdivider(0,UBRR_VALUE);

	string_clear();
	string_add_string("LCD adapter");
	copy_string_to_line(1);

	lcd_writebuffer();
	
	while(1)
	{

// 	string_clear();
// 	string_add_string("Andrew");
// 	copy_string_to_line(2);
// 
// 	lcd_writebuffer();
// 	_delay_ms(1000);

// 		if (uart_receive_line(0))
// 		{
// 			if (uart_receive_buffer_0[0]=='^')
// 			{
// 				if (uart_receive_buffer_0[1]=='CLS'){string_clear();}
// 				//if (uart_receive_buffer_0[1]=='E'){lcd_init();}
// 				//if (uart_receive_buffer_0[1]=='D'){lcd_power(0);}
// 			}else
// 			{
// 				
// 				for(int i=0; i<LCD_LINE_LENGTH; i++)
// 				{
// 					lcd_line_1[i]=uart_receive_buffer_0[i];
// 					lcd_line_2[i]=uart_receive_buffer_0[LCD_LINE_LENGTH+i];
// 				}
// 			}
// 			lcd_writebuffer();
// 		}
	}
}