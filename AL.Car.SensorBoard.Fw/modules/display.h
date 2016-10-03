#ifndef DISPALY_H_
#define DISPALY_H_

#include "..\board\board.h"
#include "..\libs\bwl_uart.h"
#include "..\libs\ds18b20_avr.h"
#include "..\libs\dht22.h"
#include "..\libs\bwl_strings.h"
#include "..\modules\voltage_data.h"


void show_data_on_display(char *data);
void show_voltage_on_display(int _duration);
void show_p_sensor_on_display(int _duration);
void show_temperature_on_display(int _duration);
void show_humidity_on_display(int _duration);
void show_all_data_on_display(int _duration);

#endif /* DISPALY_H_ */