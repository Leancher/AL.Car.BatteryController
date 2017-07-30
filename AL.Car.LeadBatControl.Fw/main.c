/*
 * AL.Car.LeadBatControl.Fw
 *
 * Created: 28.07.2016 8:44:04
 * Author : Andrew
 */ 


 //������� 16 ���, �� ����� ����������� ����� �������
 //---------------------------------------------------
#include <avr/io.h>
#include "board/board.h"

#define DEV_NAME "PS board 1.0"
#define ADC_VOLT_MULTIPLIER_MV		(68+2)/2 * 1.1
#define DIODE_CORRECTION 350

#define VOLTAGE_ENGINE_RUN 12500
#define VOLTAGE_INPUT_NORMAL 11000
#define VOLTAGE_CHARGE_ON 7200
#define VOLTAGE_CHARGE_OFF 7500
#define VOLTAGE_BATTERY_DISCHARGEOFF 5500

int voltage_generator=0;
int voltage_battery=0;
int voltage_acc=0;

int current_state=0;

int get_voltage()
{
	int val=0;
	val=adc_read_average(3)*ADC_VOLT_MULTIPLIER_MV + DIODE_CORRECTION;
	return val;
}

void device_init()
{
	//uart_init_withdivider(0,UBRR_VALUE);
	relay_battery_charge(0);
	led_yellow_set(1);
	relay_battery_power(1);
}

int main(void)
{
	wdt_enable(WDTO_8S);
	device_init();
	//������� 0 - ���, 1 - ����
    while (1) 
    {
		wdt_reset();
		adc_init_voltage_generator();
		voltage_generator=get_voltage();
		adc_init_voltage_battery();
		voltage_battery=get_voltage();
		adc_init_voltage_acc();
		voltage_acc=get_voltage();
		
		//��������� �������
		if (voltage_generator>VOLTAGE_ENGINE_RUN)
		{
			relay_battery_power(1);
			if (current_state==0)
			{
				if (voltage_battery<VOLTAGE_CHARGE_OFF)
				{
					relay_battery_charge(0);
					led_green_set(0);
					led_yellow_set(0);
					led_red_set(1);
				}
				current_state=1;
			}
			//������� ���������, �������� �����
			if (voltage_battery<VOLTAGE_CHARGE_ON)
			{
				relay_battery_charge(0);
				led_green_set(0);
				led_yellow_set(0);
				led_red_set(1);
			}
			if (voltage_battery>VOLTAGE_CHARGE_OFF)
			{
				//������� ��������, ��������� �����
				relay_battery_charge(1);
				led_yellow_set(0);
				led_green_set(1);
				led_red_set(0);
			}
		}
		//�������� ���������
		if (voltage_acc>VOLTAGE_INPUT_NORMAL)
		{
			//��������� �� �������
			if (voltage_generator<VOLTAGE_ENGINE_RUN)
			{
				//��������� ���� �������
				relay_battery_charge(1);
				//�������� ���� ��������
				relay_battery_power(1);
				//��������� ���������� �������, ������� ���������
				if (voltage_battery<VOLTAGE_BATTERY_DISCHARGEOFF)
				{
					led_green_set(0);
					led_yellow_set(0);				
					led_red_set(1);
				}
				else
				{
					//������� ��������, ��������� ��������
					led_green_set(0);
					led_yellow_set(1);
					led_red_set(0);				
				}
				current_state=0;		
			}
		}
		//��������� ���������
		if (voltage_generator<VOLTAGE_INPUT_NORMAL)
		{
			//��������� �����
			relay_battery_charge(1);
			led_green_set(1);
			led_yellow_set(0);
			led_red_set(0);
			//������� ������ ���������, ��� ���������
			if (voltage_battery<VOLTAGE_BATTERY_DISCHARGEOFF)
			{
				relay_battery_power(0);
			}
			current_state=0;
		}
		_delay_ms(1000);
    }
}