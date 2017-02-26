/*
 * AL.Car.SmartPS.Fw
 *
 * Created: 28.07.2016 8:44:04
 * Author : Andrew
 */ 


 //������� 16 ���, �� ����� ����������� ����� �������
 //---------------------------------------------------
#include <avr/io.h>
#include "board/board.h"

#define DEV_NAME "PS board 1.0"
#define ADC_VOLT_MULTIPLIER_MV		(68+2.2)/2.2 * 1.1
#define DIODE_CORRECTION 200

#define VOLTAGE_INPUT_ENGINE_RUN 13000
#define VOLTAGE_INPUT_NORMAL 11000
#define VOLTAGE_CHARGE_ON 11500
#define VOLTAGE_CHARGE_OFF 12000
#define VOLTAGE_BATTERY_DISCHARGEOFF 8000

int voltage_input=0;
int voltage_battery=0;

int get_voltage_input()
{
	adc_init_voltage_input();
	_delay_ms(1);
	int val=0;
	val=adc_read_average(3)*ADC_VOLT_MULTIPLIER_MV+DIODE_CORRECTION;
	return val;
}

int get_voltage_battery()
{
	adc_init_voltage_battery();
	_delay_ms(1);
	int val=0;
	val=adc_read_average(3)*ADC_VOLT_MULTIPLIER_MV+DIODE_CORRECTION;
	return val;
}

void device_init()
{
	//uart_init_withdivider(0,UBRR_VALUE);
	relay_charge_battery(0);
	button_power_supply_enable();
	button_car_alarm_enable();	
	led_yellow_set(1);
}

int main(void)
{
	wdt_enable(WDTO_8S);
	device_init();

    while (1) 
    {
		wdt_reset();
		
		voltage_input=get_voltage_input();
		voltage_battery=get_voltage_battery();
		
		//��������� �������
		if (voltage_input>VOLTAGE_INPUT_ENGINE_RUN)
		{
			
			relay_power_supply_set(1);
			voltage_battery=get_voltage_battery();
			//������� ���������, �������� �����
			if (voltage_battery<VOLTAGE_CHARGE_ON)
			{
				relay_charge_battery(1);
				led_green_set(0);
				led_yellow_set(0);
				led_red_set(1);
			}
			if (voltage_battery>VOLTAGE_CHARGE_OFF)
			{
				//������� ��������, ��������� �����
				relay_charge_battery(0);
				led_yellow_set(0);
				led_green_set(1);
				led_red_set(0);
			}
		}
		//�������� ���������
		if (voltage_input>VOLTAGE_INPUT_NORMAL)
		{
			//��������� �� �������
			if (voltage_input<VOLTAGE_INPUT_ENGINE_RUN)
			{
				//��������� ���� �������
				relay_charge_battery(0);
				//�������� ���� ��������
				relay_power_supply_set(1);
				//��������� ���������� �������, ������� ���������
				if (voltage_battery<VOLTAGE_BATTERY_DISCHARGEOFF)
				{
					led_green_set(0);
					led_yellow_set(0);				
					led_red_set(1);
					//��������� ��������
					//relay_power_supply_set(0);
				}
				else
				{
					//������� ��������, ��������� ��������
					led_green_set(0);
					led_yellow_set(1);
					led_red_set(0);				
				}				
			}

		}
		//��������� ���������
		if (voltage_input<VOLTAGE_INPUT_NORMAL)
		{
			//��������� �����
			relay_charge_battery(0);
			led_green_set(0);
			led_yellow_set(0);
			led_red_set(0);
			//������� ������ ���������, ��� ���������
			if (voltage_battery<VOLTAGE_BATTERY_DISCHARGEOFF)
			{
			relay_power_supply_set(0);
			}
		}
		_delay_ms(1000);
    }
}