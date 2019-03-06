
#include "sensor_elements_initiate.h"

/*
* Default constructor.
*/
SENSOR_ELEMENTS_INITIATE::SENSOR_ELEMENTS_INITIATE()
{
}

void SENSOR_ELEMENTS_INITIATE::initiate(void)
{
  Uint8 i;
  //Initialize one relais
  Relais1FromPin8.initiate("VAR.Bewaesserung", 8u, 4, TRUE, TRUE);

  //Initialize the DHT22 sensor.
  Dth22Sensor.initiate("VAR.Aussentemperatur", 2u, "VAR.AussenFeuchtigkeit");

  String data = Dth22Sensor.get_sampled_data();
  Serial.println(data);

  //A one wire temp sensor on arduino pin 3
  //OneWire tempSensorOneWire(3);
  //TempOneWireSensor.initiate("VAR.TempSensorOneWire", 3u, &tempSensorOneWire);

  //for(i = 0u; i < 255u; i++){
  //TempOneWireSensor.background_routine();

  //Serial.println(TempOneWireSensor.SampledValue);
  //}



  Serial.println("All elements registered. Starting server");
}
