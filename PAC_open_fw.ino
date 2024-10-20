
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

#include "functions.h"
#include "define.h"
#include "tempSensor.h"


void setup(){

    Serial.begin(115200);

    tft.begin(i2c_Address, true); // Address 0x3C default
    tft.clearDisplay();
    tft.display();

    tft.setTextSize(1);
    tft.setTextColor(SH110X_WHITE);

    Serial.println();Serial.println();Serial.println();Serial.println();

    setupPin();
    setReferenceCurrent(); 

    temp_waterTop = new tempSensor(PIN_TEMP_WATER_TOP, serie_resistor_water_top, reference_coefficients_water_top);
    temp_waterPipe = new tempSensor(PIN_TEMP_WATER_PIPE , serie_resistor_water_pipe, reference_coefficients_water_pipe);
    temp_heatExchanger = new tempSensor(PIN_TEMP_HEAT_EXCHANGER , serie_resistor_heat_exchanger, reference_coefficients_heat_exchanger);
    temp_evap = new tempSensor(PIN_TEMP_AIR_FLOW_EVAP , serie_resistor_air_flux_evap, reference_coefficients_air_flux_evap);
    
    allOff();
    delay(2500);    //prevent false start when rebooting

}


void loop(){

    //updateSensors();
    //testSequence();

    if(millis() - timer_update_sensors > update_sensor_delay ){
        timer_update_sensors = millis();

        Serial.print("Update Sensors:");
        temp_waterTop->updateSensor();
        temp_waterPipe->updateSensor();
        temp_heatExchanger->updateSensor();
        temp_evap->updateSensor();
        Serial.println("Done");

    }

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
        tft.print( temp_waterTop->getAvgTemp() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        tft.print("water pipe: ");
        tft.print(temp_waterPipe->getAvgTemp() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();


        tft.print("heat ex:    ");
        tft.print( temp_heatExchanger->getAvgTemp() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        tft.print("temp_evap:       ");
        tft.print( temp_evap->getAvgTemp() );
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
    if( temp_waterTop->getAvgTemp() > 40 || temp_waterPipe->getAvgTemp() > 40 ){

        if(print_flag){
            Serial.println(" - STOP, TEMP OK");
            printTempSensorReport();
        }

    //temperature error
    }else if(temp_waterTop->getAvgTemp() > 70 || temp_waterPipe->getAvgTemp() > 70 || temp_heatExchanger->getAvgTemp() > 80){
            
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

        if(temp_heatExchanger->getAvgTemp() > 68 ){
            //off
            digitalWrite(PIN_FAN_LOW_SPEED, 0);
            digitalWrite(PIN_FAN_HIGH_SPEED, 0);
            digitalWrite(PIN_COMPRESSOR, 0);
            digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);
            digitalWrite(PIN_WATER_PUMP, 1);

        }else if(temp_heatExchanger->getAvgTemp() < 60){
            //on
            digitalWrite(PIN_FAN_LOW_SPEED, 1);
            digitalWrite(PIN_FAN_HIGH_SPEED, 0);
            digitalWrite(PIN_COMPRESSOR, 1);
            digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);
            
            digitalWrite(PIN_WATER_PUMP, 1);
        }

        //make the water pump work in any case
        digitalWrite(PIN_WATER_PUMP, 1);

        if( temp_evap->getAvgTemp() < 17.5){
            digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 1);
        }else if(temp_evap->getAvgTemp() > 18.5){
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