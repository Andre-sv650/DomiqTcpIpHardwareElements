

#include "datatypes/cpu_datatypes.h"
#include "connected_hardware_elements/dht22_element.h"
#include "connected_hardware_elements/relais_element.h"
#include "connected_hardware_elements/temp_sensor_one_wire_element.h"
#include "connected_hardware_elements/bhi1750fvi_light_intensity.h"
//#include "connected_hardware_elements/light_intensity_element.h"

#ifndef SENSOR_ELEMENTS_INITIATE_H
#define SENSOR_ELEMENTS_INITIATE_H

class SENSOR_ELEMENTS_INITIATE
{
//Fields
public:
  
  SENSOR_ELEMENTS_INITIATE();
  
  // Intiate all sensors
  void initiate();  

  //Relais outputs.
  RELAIS_ELEMENT Relais1FromPin8;

  DHT22_ELEMENT Dth22Sensor;

  TEMP_SENSOR_ONE_WIRE_ELEMENT TempOneWireSensor;

  BHI_1750FVI_LIGHT_INTENSITY LightIntensitySensor;
  
private:
};


#endif //SENSOR_ELEMENTS_INITIATE_H

