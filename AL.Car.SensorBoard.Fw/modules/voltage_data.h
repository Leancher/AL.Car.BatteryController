#ifndef VOLTAGE_DATA_H_
#define VOLTAGE_DATA_H_

#define ADC_VOLT_MULTIPLIER_MV		(68+2.2)/2.2 * 1.1

float get_battery_voltage();
float get_photo_sensor_voltage();

#endif /* VOLTAGE_DATA_H_ */