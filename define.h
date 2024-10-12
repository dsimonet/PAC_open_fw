
#ifndef __DEFINE_H__
#define __DEFINE_H__

//ACTUACTOR
const uint8_t PIN_FAN_HIGH_SPEED = 11;
const uint8_t PIN_FAN_LOW_SPEED = 7;
const uint8_t PIN_COMPRESSOR = 4;
const uint8_t PIN_BYPASS_PRESSURE_REDUCER = 9;
const uint8_t PIN_LEGACY_RESISTOR_HEAT = 5;
const uint8_t PIN_WATER_PUMP = 8;

//SENSORS
const uint8_t PIN_TEMP_WATER_TOP = A0;
const uint8_t PIN_TEMP_WATER_PIPE = A1;
const uint8_t PIN_TEMP_HEAT_EXCHANGER = A2;
const uint8_t PIN_TEMP_AIR_FLOW_EVAP = A3;

//ACHS-7121 current sensor
const uint8_t PIN_CURRENT_SENSOR = A4;

//PCF8563T TIMER
const uint8_t RTC_ADDR_Write = 0xA2;
const uint8_t RTC_ADDR_Read =  0xA2+1;

//Final State Machine

typedef enum FSM_t {
    FSM_reset = 0,

    FSM_init = 10,
    FSM_idle,
    FSM_heat_pump_working,
    FSM_legacy_resistor,

    FSM_test = 50,
    FSM_error,
};

FSM_t fsm = FSM_reset;


#endif //guard