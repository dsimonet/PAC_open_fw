
#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

//DISPLAY

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G tft = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//ACTUACTOR
const uint8_t PIN_FAN_HIGH_SPEED = 11;
const uint8_t PIN_FAN_LOW_SPEED = 7;
const uint8_t PIN_COMPRESSOR = 4;
const uint8_t PIN_BYPASS_PRESSURE_REDUCER = 9;
const uint8_t PIN_LEGACY_RESISTOR_HEAT = 5;
const uint8_t PIN_WATER_PUMP = 8;

//SENSORS

//see https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
// C1 e-3, C2 e-4, C3 e-7
const float reference_coefficients_water_top[3] =       {0.8152350653e-03, 2.948759503e-04, -2.253994324e-07};
const float reference_coefficients_water_pipe[3] =      {-0.03240305442e-03, 4.401381657e-04, -8.145708226e-07};
const float reference_coefficients_heat_exchanger[3] =  {0.8152350653e-03, 2.948759503e-04, -2.253994324e-07};
const float reference_coefficients_air_flux_evap[3] =   {0.3426591640e-03, 3.554302673e-04, -2.820340671e-07};

const float serie_resistor_water_top = 3300;
const float serie_resistor_water_pipe = 10000;
const float serie_resistor_heat_exchanger = 10000;
const float serie_resistor_air_flux_evap = 22000;

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