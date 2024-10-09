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

void testSequence(){

    uint32_t timerLocal_001 = millis();
    uint32_t timerLocal_002 = millis();

    //Fan low speed
    digitalWrite(PIN_FAN_LOW_SPEED, 1);
    while(millis() - timerLocal_001 < 10e3){
        if(millis() - timerLocal_002 > 100){
            timerLocal_002 = millis();
            Serial.print(F("Fan low speed : "));
            Serial.print( (millis() - timerLocal_001) / 1000);
            Serial.print(" ");
            Serial.println(analogRead(PIN_CURRENT_SENSOR) );
        }
    }
    digitalWrite(PIN_FAN_LOW_SPEED, 0);
    timerLocal_001 = millis();

    Serial.println("pause");
    delay(1000);

     //Fan high speed
    digitalWrite(PIN_FAN_HIGH_SPEED, 1);
    while(millis() - timerLocal_001 < 10e3){
        if(millis() - timerLocal_002 > 100){
            timerLocal_002 = millis();
            Serial.print(F("Fan high speed : "));
            Serial.print( (millis() - timerLocal_001) / 1000);
            Serial.print(" ");
            Serial.println(analogRead(PIN_CURRENT_SENSOR) );
        }
    }
    digitalWrite(PIN_FAN_HIGH_SPEED, 0);
    timerLocal_001 = millis();

    Serial.println("pause");
    delay(1000);

    //bypass pressure reducer on, to help motor to start
    //then start compressor,
    //then close bypass
    digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 1);
    delay(1000);
    digitalWrite(PIN_COMPRESSOR, 1);
    while(millis() - timerLocal_001 < 10e3){
        
        if(millis() - timerLocal_001 > 3e3){
            digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);   
        }

        if(millis() - timerLocal_002 > 100){

            if(digitalRead(PIN_BYPASS_PRESSURE_REDUCER) == 1 ){
                Serial.print("BYPASS ON ");
            }else{
                Serial.print("BYPASS OFF ");
            }
            timerLocal_002 = millis();
            Serial.print(F("compressor : "));
            Serial.print( (millis() - timerLocal_001) / 1000);
            Serial.print(" ");
            Serial.println(analogRead(PIN_CURRENT_SENSOR) );
        }
    }
    digitalWrite(PIN_COMPRESSOR, 0);
    timerLocal_001 = millis();

    Serial.println("pause");
    delay(1000);

    //Water pump
    digitalWrite(PIN_WATER_PUMP, 1);
    while(millis() - timerLocal_001 < 10e3){
        if(millis() - timerLocal_002 > 100){
            timerLocal_002 = millis();
            Serial.print(F("Water pump : "));
            Serial.print( (millis() - timerLocal_001) / 1000);
            Serial.print(" ");
            Serial.println(analogRead(PIN_CURRENT_SENSOR) );
        }
    }
    digitalWrite(PIN_WATER_PUMP, 0);
    timerLocal_001 = millis();

    Serial.println("pause");
    delay(1000);

    //Heat resistor
    digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 1);
    while(millis() - timerLocal_001 < 10e3){
        if(millis() - timerLocal_002 > 100){
            timerLocal_002 = millis();
            Serial.print(F("Heat resistor : "));
            Serial.println(analogRead(PIN_CURRENT_SENSOR) );
        }
    }
    digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 0);
    timerLocal_001 = millis();

    Serial.println("Test Sequence done");
    delay(1000);

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