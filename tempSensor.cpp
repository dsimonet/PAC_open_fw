#include "tempSensor.h"


tempSensor::tempSensor(uint8_t _pin, const uint16_t _serie_res, const float _ref_coef[] ){
    this->pin = _pin;
    this->serie_res = _serie_res;

    this->ref_coef[0] = _ref_coef[0];
    this->ref_coef[1] = _ref_coef[1];
    this->ref_coef[2] = _ref_coef[2];

    pinMode(pin, INPUT);

    //set history size
    this->history_lenght = sizeof(history)/sizeof(history[0]);
    // Serial.print("history leng:");
    // Serial.println(history_lenght);

    for(uint8_t i = 0 ; i < history_lenght; i++){
        history[i] = 0;
    }

    //fill the history
    for(uint8_t i = 0 ; i < history_lenght; i++){

        bool status = updateSensor();

        // if( status == 0){
        //     Serial.println("Fail reading sensors!");
        // }else{
        //     Serial.print(" ");
        //     Serial.print(i);
        //     Serial.print(" ");
        //     Serial.print(last_temp);
        // }
        // Serial.println(".");
    }

}

bool tempSensor::updateSensor(void){

    float logR1, NTC, T, Tc;
    last_mes = analogRead(pin);

    if(last_mes == 0 || last_mes == 1023){
        last_temp -273.15f; 
        return 0;
    }

    NTC =  (last_mes * serie_res) / (1023 - last_mes);
    logR1 = log(NTC);
    T = (1.0 / (ref_coef[0] + ref_coef[1]*logR1 + ref_coef[2]*logR1*logR1*logR1));
    Tc = T - 273.15;

    last_temp = Tc;

    // Serial.print("mes:");
    // Serial.print(last_temp);

    avrgValues();

    return 1;

}

bool tempSensor::avrgValues(){  

    // Serial.println();
    // for(uint8_t i = history_lenght ; i >= 1  ; i--){
    //     Serial.print(i);
    //     Serial.print("[");
    //     Serial.print(history[i-1]);
    //     Serial.print("]");
    // }
    // Serial.println();

    // history[0] is the newest
    for(uint8_t i = history_lenght ; i >= 1  ; i--){
        history[i-1] = history[i-2];
    }

    history[0] = last_temp;

    // for(uint8_t i = history_lenght ; i >= 1  ; i--){
    //     Serial.print(i);
    //     Serial.print("[");
    //     Serial.print(history[i-1]);
    //     Serial.print("]");
    // }
    // Serial.println();

    float acc = 0;
    for(uint8_t i = 0; i < history_lenght; i++){
        acc += history[i];
    }
    lastAvrgTemp = acc / history_lenght;


    return 1;
}

