
#include "functions.h"
#include "define.h"

void setup(){

    Serial.begin(115200);
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
const uint32_t print_delay = 10e3;
bool print_flag = true;


void loop(){

    //updateSensors();
    //testSequence();

    if(millis() - timer_print_data > print_delay){
        print_flag = true;
        timer_print_data = millis();
    }

    if(print_flag){
        printTempSensorReport();
        Serial.print(", ");
        printReadableCurrent();
        
    }
    
    if(analogRead(PIN_TEMP_HEAT_EXCHANGER) < 510){
        //off
        forceCoolDown();

        if(print_flag)
            Serial.print(" - OFF");
    }else if(analogRead(PIN_TEMP_HEAT_EXCHANGER) > 540){
        //on
        forceSystem();

        if(print_flag)
            Serial.print(" - ON");
    }

    
    

    if( analogRead(PIN_TEMP_WATER_TOP) > 250 || analogRead(PIN_TEMP_WATER_PIPE) < 470 ){
         while (1)
         {
            
            Serial.println(" STOP TEMP ERROR !!!");
            printTempSensorReport();
            delay(60e3);

         }
         
    }

    if(print_flag){
        Serial.println();
    }
    print_flag = false;



}