#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

class tempSensor{

    public:
    tempSensor(uint8_t pin, const uint16_t serie_res, const float ref_coef[] );
    void updateSensor(void);
    float getAvgTemp(void);

    private :

    uint8_t pin;
    uint16_t serie_res;
    float ref_coef[3];
    uint16_t lastRead[10];
};

#endif