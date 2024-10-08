#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "define.h"

void setupPin(){
//ACTUACTOR
pinMode(PIN_FAN_LOW_SPEED, OUTPUT);
pinMode(PIN_FAN_HIGH_SPEED, OUTPUT);
pinMode(PIN_COMPRESSOR, OUTPUT);
pinMode(PIN_BYPASS_PRESSURE_REDUCER, OUTPUT);
pinMode(PIN_LEGACY_RESISTOR_HEAT, OUTPUT);
pinMode(PIN_WATER_PUMP, OUTPUT);

//SENSORS
pinMode(PIN_TEMP_WATER_TOP, INPUT);
pinMode(PIN_TEMP_WATER_PIPE, INPUT);
pinMode(PIN_TEMP_HEAT_EXCHANGER, INPUT);
pinMode(PIN_TEMP_AIR_FLOW_EVAP, INPUT);

//ACHS-7121 current sensor
pinMode(PIN_CURRENT_SENSOR, INPUT);

}

void setupTimer(){

}

void setupCurrentSensor(){

}

void checkSensors(){

}


void setModeFsm(){

}

void updateSensors(){

}


#endif //guard