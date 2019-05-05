

#include "../src/datatypes/cpu_datatypes.h"
#include "../src/connected_hardware_elements/DHT22/dht22_element.h"
#include "../src/connected_hardware_elements/interrupt/interrupt_element.h"

#ifndef SENSOR_ELEMENTS_KELLER_INITIATE_H
#define SENSOR_ELEMENTS_KELLER_INITIATE_H

class SENSOR_ELEMENTS_KELLER_INITIATE
{
//Fields
public:
  
  SENSOR_ELEMENTS_KELLER_INITIATE();
  
  // Intiate all sensors
  void initiate();

  DHT22_ELEMENT Dth22Sensor;

  INTERRUPT_ELEMENT S0CounterForDrainage1;
  
private:
};


#endif //SENSOR_ELEMENTS_KELLER_INITIATE_H

