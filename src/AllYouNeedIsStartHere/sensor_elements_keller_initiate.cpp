
#include "sensor_elements_keller_initiate.h"

/*
* Default constructor.
*/
SENSOR_ELEMENTS_KELLER_INITIATE::SENSOR_ELEMENTS_KELLER_INITIATE()
{
}



void SENSOR_ELEMENTS_KELLER_INITIATE::initiate(void)
{
  //Initialize the DHT22 sensor.
  //DHT22 Sensor needs a pull up resisor between SCL and VCC.
  Dth22Sensor.initiate("VAR.AnschlusskellerTemperatur", 5u, "VAR.AnschlusskellerFeuchtigkeit");

  S0CounterForDrainage1.initiate("VAR.DrainagePumpe1", 2u, 160u, TRUE);

  //All elements registered.
  //Serial.println("All elements registered. Starting server");
}
