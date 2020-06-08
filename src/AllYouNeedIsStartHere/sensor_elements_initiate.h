#ifdef ARDUINO_MEGA

#include "datatypes/cpu_datatypes.h"
#include "connected_hardware_elements/DHT22/dht22_element.h"
#include "connected_hardware_elements/Relais/relais_element.h"
#include "connected_hardware_elements/temp_sensor/temp_sensor_one_wire_element.h"
#include "connected_hardware_elements/light_intensity/bhi1750fvi_light_intensity.h"
#include "connected_hardware_elements/Relais/relais_element_self_locked.h"
#include "connected_hardware_elements/stm_vl53l0x_element.h"
#include "connected_hardware_elements/keypad/keypad_4_4.h"
#include "connected_hardware_elements/ultrasonic/ultrasonic_sr04t_element.h"
#include "connected_hardware_elements/interrupt/interrupt_element.h"
#include "connected_hardware_elements/RcSwitch433Mhz/rc_switch_433_mhz.h"

#ifndef SENSOR_ELEMENTS_INITIATE_H
#define SENSOR_ELEMENTS_INITIATE_H

//The maximum on time for the relais is set to 10 minutes = 60000ms.
//This is needed in case that the connection to domiq is broken and you are on holidays.
#define MAXIMUM_TIME_FOR_RELAIS 600000u

class SENSOR_ELEMENTS_INITIATE
{
//Fields
public:
  
  SENSOR_ELEMENTS_INITIATE();
  
  // Intiate all sensors
  void initiate();  

  //Relais outputs.
  RELAIS_ELEMENT RelaisForGartenpumpe;

  RELAIS_ELEMENT RelaisForGartenSprenger;

  RELAIS_ELEMENT_SELF_LOCKED Electrical24VPowerSupply;

  RELAIS_ELEMENT_SELF_LOCKED PowerSupplyPumpeAndBuchsbaumBeleuchtung;

  DHT22_ELEMENT Dth22Sensor;

  TEMP_SENSOR_ONE_WIRE_ELEMENT TempOneWireSensor;

  BHI_1750FVI_LIGHT_INTENSITY LightIntensitySensor;

  //STM_VL53L0X_ELEMENT StmVl53Element;

  ULTRASONIC_SR04T_ELEMENT Drainage1;

  ULTRASONIC_SR04T_ELEMENT Drainage2;

  INTERRUPT_ELEMENT PhotovoltaicPlantS0Element;

  INTERRUPT_ELEMENT RainMeasurementElement;

  RC_SWITCH_433MHZ_ELEMENT RcSwitchElement;

  //KEYPAD_4_4_ELEMENT KeyPad;
  
private:
};

#endif //SENSOR_ELEMENTS_INITIATE_H

#endif //ARDUINO_MEGA

