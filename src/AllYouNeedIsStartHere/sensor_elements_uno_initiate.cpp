
#include "sensor_elements_uno_initiate.h"

/*
* Default constructor.
*/
SENSOR_ELEMENTS_UNO_INITIATE::SENSOR_ELEMENTS_UNO_INITIATE()
{
}



void SENSOR_ELEMENTS_UNO_INITIATE::initiate(void)
{
  // Receiver on interrupt 0 => that is pin #2, Sender on pin 5
  RC_SWITCH_433MHZ_BASE_INSTANCE::initiate(0, 5u);
  RcSwitchElement.initiate("VAR.RcSwitchTestVar", 1394001, 1394004);

  SoilMoisture1.initiate(0, "VAR.FeuchtigkeitKeller1");

  //All elements registered.
  Serial.println("All elements registered. Starting server");
}
