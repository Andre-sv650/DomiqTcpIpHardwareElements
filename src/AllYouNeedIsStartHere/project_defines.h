//---------------------Setup a new key if the EEPROM should be erased.--------------------
#define EEPROM_KEY1 1
#define EEPROM_KEY2 2

//The communication speed with linux or windows.
#define SERIAL_COMMUNICATION_SPEED 115200

//Save the data to the EEPROM every minute. Else the eeprom is destroyed after small time by too many write attmepts.
#define INTERRUPT_ELEMENT_SAVE_DATA_TO_EEPROM_TIME 60000


//---------------The maximum number of connected elements like DHT22, temp seonsor elements one wire etc. -------------
#define CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH 10

//-------------------------------Defines for the enabled elements.-------------------------------------
#define RELAIS_ELEMENT_ENABLED //Define it to use relay elements.
#define RELAIS_ELEMENT_MAX_NUMBER_OF_RELAIS 8 //The maximum number of relais per relais element.

//The relais element self locked switch on and off time in milli seconds.
//Normally a relais dont need more than 80ms to be switched on and off. We use 250ms to be on the safe side.
#define RELAIS_ELEMENT_SELF_LOCKED_RELAIS_ON_OFF_TIME 250


#define DHT22_ELEMENT_ENABLED //Define it to used DHT22 elements
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED // Define it to use one wire external temperature sensors.


#define BHI_1750FVI_LIGHT_INTENSITY_ENABLED //Define it to use I2C BHI1750FVI light sensor.
#define ULTRASONIC_SR04T_ELEMENT_ENABLED //Define it to use ultrasonic SR04T range sensor.


//#define STM_VL53L0X_ELEMENT_ENABLED //Define it to use STM VL53LOX range sensor.
#define KEYPAD_4_4_ELEMENT_ENABLED //Define it to use the 4_4 keypad element.

#define RC_SWITCH_433MHZ_ENABLED //Define it to use the RC switch (incoming data from RC control)
#define RC_SENDER_433MHZ_ENABLED //Define it to use the RC sender. Enable or disble external components like external power plugs.


//#define PRESENCE_DETECTOR_ELEMENT_ENABLED


#define MaximumNumberOfInterrupts 10
#define INTERRUPT_ELEMENT_ENABLED
