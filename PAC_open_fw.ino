
#include "functions.h"
#include "define.h"






void setup(){

Serial.begin(115200);
Serial.println();Serial.println();Serial.println();Serial.println();
Serial.println(" -- PAC FW init start -- ");
Serial.print("Init GPIO:");             setupPin();             Serial.println("done");
Serial.print("Check temp Sensors:");    checkSensors();         Serial.println("done");
Serial.print("Init Current Sensor:");   setupCurrentSensor();   Serial.println("done");
Serial.print("Init Timer:");            setupTimer();           Serial.println("done");
Serial.print("Switch FSM:");            setModeFsm();           Serial.println("done");
Serial.println(" -- PAC FW init done -- ");

}


void loop(){

//updateSensors();

testSequence();
while(1);


}