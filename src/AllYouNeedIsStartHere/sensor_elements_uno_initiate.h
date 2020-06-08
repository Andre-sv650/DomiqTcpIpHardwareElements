

#include "../src/datatypes/cpu_datatypes.h"
#include "../src/connected_hardware_elements/DHT22/dht22_element.h"
#include "../src/connected_hardware_elements/interrupt/interrupt_element.h"
#include "../src/connected_hardware_elements/Relais/relais_element.h"
#include "../src/connected_hardware_elements/RcSwitch433Mhz/rc_switch_433_mhz.h"
#include "../src/connected_hardware_elements/RcSwitch433Mhz/rc_switch_433_mhz_base_instance.h"
#include "../src/connected_hardware_elements/soil_moisture_analog/analog_sensor_element.h"

#ifndef SENSOR_ELEMENTS_UNO_INITIATE_H
#define SENSOR_ELEMENTS_UNO_INITIATE_H

class SENSOR_ELEMENTS_UNO_INITIATE
{
//Fields
public:
  
  SENSOR_ELEMENTS_UNO_INITIATE();
  
  // Intiate all sensors
  void initiate();

  /* Interrupt element, connect the interrupt pin to ground to set one interrupt.
   The counter is incremented, if the interrupt pin is released from ground.
  */
  RC_SWITCH_433MHZ_ELEMENT RcSwitchElement;

  ANALOG_SENSOR_ELEMENT SoilMoisture1;
};


#endif //SENSOR_ELEMENTS_UNO_INITIATE_H

