#define KELLER

//---------------------Setup a new key if the EEPROM should be erased.--------------------
#define EEPROM_KEY1 1
#define EEPROM_KEY2 2


//---------------The maximum number of connected elements like DHT22, temp seonsor elements one wire etc. -------------
#define CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH 6



//-------------------------------Defines for the enabled elements.-------------------------------------
#define RELAIS_ELEMENT_ENABLED //Define it to use relay elements.

//The relais element self locked switch on and off time in milli seconds.
//Normally a relais dont need more than 80ms to be switched on and off. We use the double time.
#define RELAIS_ELEMENT_SELF_LOCKED_RELAIS_ON_OFF_TIME 160


#define DHT22_ELEMENT_ENABLED //Define it to used DHT22 elements
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED // Define it to use one wire external temperature sensors.


#define BHI_1750FVI_LIGHT_INTENSITY_ENABLED //Define it to use I2C BHI1750FVI light sensor.
#define ULTRASONIC_SR04T_ELEMENT_ENABLED //Define it to use ultrasonic SR04T range sensor.


//#define STM_VL53L0X_ELEMENT_ENABLED //Define it to use STM VL53LOX range sensor.
//#define KEYPAD_4_4_ELEMENT_ENABLED //Define it to use the 4_4 keypad element.


//#define PRESENCE_DETECTOR_ELEMENT_ENABLED


#define MaximumNumberOfInterrupts 2
#define INTERRUPT_ELEMENT_ENABLED
