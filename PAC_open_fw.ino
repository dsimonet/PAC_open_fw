
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
    // Serial.print("Check temp Sensors:");    checkSensors();         Serial.println("done");
    // Serial.print("Init Current Sensor:");   setupCurrentSensor();   Serial.println("done");
    // Serial.print("Init Timer:");            setupTimer();           Serial.println("done");
    // Serial.print("Switch FSM:");            setModeFsm();           Serial.println("done");
    Serial.println(" -- PAC FW init done -- ");

    allOff();


}

uint32_t timer_print_data = 60e3;
const uint32_t print_delay = 100;
bool print_flag = true;


void loop(){

    //updateSensors();
    //testSequence();

    if(millis() - timer_print_data > print_delay){
        print_flag = true;
        timer_print_data = millis();
        tft.clearDisplay();
    }

    if(print_flag){
        printTempSensorReport();
        Serial.print(", ");
        printReadableCurrent();

        tft.setCursor(0, 0);
        tft.print("water top:  ");
        tft.print(getCorrectedTemp_waterTop() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        //tft.setCursor(0, 1);
        tft.print("water pipe: ");
        tft.print(getCorrectedTemp_waterPipe() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        //tft.setCursor(0, 0);
        tft.print("heat ex:    ");
        tft.print(getCorrectedTemp_heatExchanger() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        //tft.setCursor(0, 0);
        tft.print("evap:       ");
        tft.print( getCorrectedTemp_air_flux_evap() );
        tft.print( (char)247 ); tft.print("C");
        tft.println();

        tft.display();
    }
    
    if(getCorrectedTemp_heatExchanger() < 50.0 ){
        //off
        forceCoolDown();

        if(print_flag)
            Serial.print(" - OFF");
    }else if(getCorrectedTemp_heatExchanger() > 60){
        //on
        forceSystem();

        if(print_flag)
            Serial.print(" - ON");
    }

    
    

    // if( analogRead(PIN_TEMP_WATER_TOP) > 50 || analogRead(PIN_TEMP_WATER_PIPE) >70 ){
    //      while (1)
    //      {
            
    //         Serial.println(" STOP TEMP ERROR !!!");
    //         printTempSensorReport();
            
    //         delay(60e3);

    //      }
         
    // }

    if(print_flag){
        Serial.println();
    }
    print_flag = false;



}