
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#include "functions.h"
#include "define.h"

void setup(){

    Serial.begin(115200);

    tft.begin(i2c_Address, true); // Address 0x3C default
    tft.clearDisplay();
    tft.display();

    tft.setTextSize(1);
    tft.setTextColor(SH110X_WHITE);

    Serial.println();Serial.println();Serial.println();Serial.println();
    Serial.println(" -- PAC FW init start -- ");
    Serial.print("Init GPIO:");             setupPin();             Serial.println("done");
    Serial.print("Set current reference"); setReferenceCurrent();   Serial.println("done");
    Serial.print("Check temp Sensors:");    checkSensors();         Serial.println("done");
    // Serial.print("Init Current Sensor:");   setupCurrentSensor();   Serial.println("done");
    // Serial.print("Init Timer:");            setupTimer();           Serial.println("done");
    // Serial.print("Switch FSM:");            setModeFsm();           Serial.println("done");
    Serial.println(" -- PAC FW init done -- ");

    allOff();


}

uint32_t timer_update_serial = 60e3;   // not zero to get instant update   
uint32_t timer_update_display = 0;
const uint32_t serial_update_delay = 10e3;
const uint32_t display_update_delay = 100;
bool print_flag = true;


void loop(){

    //updateSensors();
    //testSequence();

    if(millis() - timer_update_serial > serial_update_delay){
        print_flag = true;
        timer_update_serial = millis();
    }

    if(print_flag){
        printTempSensorReport();
        Serial.print(", ");
        printReadableCurrent();
    }

    if(millis() - timer_update_display > display_update_delay){
        timer_update_display = millis();

        tft.clearDisplay();
        tft.setCursor(0, 0);

        tft.print("water top:  ");
        tft.print( getCorrectedTemp_waterTop() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        tft.print("water pipe: ");
        tft.print(getCorrectedTemp_waterPipe() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();


        tft.print("heat ex:    ");
        tft.print(getCorrectedTemp_heatExchanger() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        tft.print("evap:       ");
        tft.print( getCorrectedTemp_air_flux_evap() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        if(digitalRead(PIN_COMPRESSOR) ){
            tft.print(" - COMP ON");
        }else{
            tft.print(" - COMP OFF");
        }

        if(digitalRead(PIN_LEGACY_RESISTOR_HEAT) ){
            tft.print(" - RES ON");
        }else{
            tft.print(" - RES OFF");
        }

        tft.display();
    }
    
    //température ok
    if( getCorrectedTemp_waterTop() > 40 || getCorrectedTemp_waterPipe() > 40 ){

        if(print_flag){
            Serial.println(" - STOP, TEMP OK");
            printTempSensorReport();
        }

    //temperature error
    }else if(getCorrectedTemp_waterTop() > 70 || getCorrectedTemp_waterPipe() > 70 || getCorrectedTemp_heatExchanger() > 80){
            
            while (1)
            {   
                Serial.println(" - STOP, TEMP ERROR");
                printTempSensorReport();
                digitalWrite(PIN_FAN_LOW_SPEED, 0);
                digitalWrite(PIN_FAN_HIGH_SPEED, 1);
                digitalWrite(PIN_COMPRESSOR, 0);
                digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);
                digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 0);
                digitalWrite(PIN_WATER_PUMP, 1);

                delay(60e3);
            }

         
    }else{

        if(getCorrectedTemp_heatExchanger() > 68 ){
            //off
            digitalWrite(PIN_FAN_LOW_SPEED, 0);
            digitalWrite(PIN_FAN_HIGH_SPEED, 0);
            digitalWrite(PIN_COMPRESSOR, 0);
            digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);
            digitalWrite(PIN_WATER_PUMP, 1);

        }else if(getCorrectedTemp_heatExchanger() < 60){
            //on
            digitalWrite(PIN_FAN_LOW_SPEED, 1);
            digitalWrite(PIN_FAN_HIGH_SPEED, 0);
            digitalWrite(PIN_COMPRESSOR, 1);
            digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);
            
            digitalWrite(PIN_WATER_PUMP, 1);
        }

        //make the water pump work in any case
        digitalWrite(PIN_WATER_PUMP, 1);

        if(getCorrectedTemp_air_flux_evap() < 18){
            digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 1);
        }else if(getCorrectedTemp_air_flux_evap() > 18){
             digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 0);
        }


        if(print_flag){
            if(digitalRead(PIN_COMPRESSOR) ){
                Serial.print(" - COMP ON");
            }else{
                Serial.print(" - COMP OFF");
            }

            if(digitalRead(PIN_LEGACY_RESISTOR_HEAT) ){
                Serial.print(" - RES ON");
            }else{
                Serial.print(" - RES OFF");
            }

        }

    }

    if(print_flag){
        Serial.println();
    }
    print_flag = false;



}