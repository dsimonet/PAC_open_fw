
#include "functions.h"
#include "define.h"


void setup(){

Serial.begin(115200);
Serial.println();Serial.println();Serial.println();Serial.println();
Serial.println(" -- PAC FW init start -- ");
Serial.print("Init GPIO:");             setupPin();             Serial.println("done");
Serial.print("Check temp Sensors:");     checkSensors();         Serial.println("done");
Serial.print("Init Current Sensor:");   setupCurrentSensor();   Serial.println("done");
Serial.print("Init Timer:");            setupTimer();           Serial.println("done");
Serial.print("Switch FSM:");            setModeFsm();           Serial.println("done");
Serial.println(" -- PAC FW init done -- ");

}


void loop(){

//updateSensors();

digitalWrite(PIN_FAN_LOW_SPEED, 1);
delay(5000);
digitalWrite(PIN_FAN_LOW_SPEED, 0);
delay(1000);

digitalWrite(PIN_FAN_HIGH_SPEED, 1);
delay(5000);
digitalWrite(PIN_FAN_HIGH_SPEED, 0);
delay(1000);

digitalWrite(PIN_COMPRESSOR, 1);
delay(1000);
digitalWrite(PIN_COMPRESSOR, 0);
delay(1000);

digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 1);
delay(1000);
digitalWrite(PIN_BYPASS_PRESSURE_REDUCER, 0);
delay(1000);

digitalWrite(PIN_WATER_PUMP, 1);
delay(5000);
digitalWrite(PIN_WATER_PUMP, 0);
delay(1000);

digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 1);
delay(10000);
// digitalWrite(PIN_LEGACY_RESISTOR_HEAT, 0);
// delay(1000);

while(1){
    Serial.print(analogRead(PIN_TEMP_WATER_TOP) );
    Serial.print(" ");
    Serial.print(analogRead(PIN_TEMP_HEAT_EXCHANGER) );
    Serial.print(" ");
    Serial.print(analogRead(PIN_TEMP_WATER_PIPE) );
    Serial.print(" ");
    Serial.print(analogRead(PIN_TEMP_AIR_FLOW_EVAP) );
    Serial.print(" ");
    Serial.print(analogRead(PIN_CURRENT_SENSOR) );
    Serial.print(" ");
    Serial.println();
    delay(100);
}


}