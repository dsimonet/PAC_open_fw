#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

#include "Arduino.h"

class tempSensor{

    public:

    tempSensor(uint8_t _pin, const uint16_t _serie_res, const float _ref_coef[] );

    bool updateSensor(void);
    bool avrgValues(void);
    float getAvgTemp(void) {return lastAvrgTemp;};

    private :

    uint8_t pin;
    uint16_t last_mes;
    float last_temp;
    uint16_t serie_res;
    float lastAvrgTemp ;
    float ref_coef[3];

    float history[10];
    uint8_t history_lenght;

};

#endif