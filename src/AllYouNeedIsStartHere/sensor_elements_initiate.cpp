
#include "sensor_elements_initiate.h"

/*
* Default constructor.
*/
SENSOR_ELEMENTS_INITIATE::SENSOR_ELEMENTS_INITIATE()
{
}

void SENSOR_ELEMENTS_INITIATE::initiate(void)
{
  //Initialize one relais
  Relais1FromPin8.initiate("VAR.Bewaesserung", 8u, 4, TRUE, TRUE);

  //Initialize the DHT22 sensor.
  Dth22Sensor.initiate("VAR.Aussentemperatur", 2u, "VAR.AussenFeuchtigkeit");

  //A one wire temp sensor on arduino pin 12
  TempOneWireSensor.initiate("VAR.TempSensorOneWire", 12u);

  //Ligth intensity element. Connect VCC with 5V, GND with GND.
  //On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
  //On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
  //See https://www.arduino.cc/en/Reference/Wire for details.
  LightIntensitySensor.initiate("VAR.AussenHelligkeit");

  Serial.println("All elements registered. Starting server");
}
