#include "tempSensor.h"


void tempSensor::updateSensor(void){

    

}

float getCorrectedTemp(uint8_t pin, float serie_resistor,  const float coeff[]){

    int Vo;
    float logR1, NTC, T, Tc;

    Vo = analogRead(pin);

    if(Vo == 0 || Vo == 1023)
        return -273.15f; 

    NTC =  (Vo * serie_resistor) / (1023 - Vo);
    logR1 = log(NTC);
    T = (1.0 / (coeff[0] + coeff[1]*logR1 + coeff[2]*logR1*logR1*logR1));
    Tc = T - 273.15;

    return Tc;
}