
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
  Relais1FromPin8.initiate("VAR.Bewaesserung", 30u, 8, TRUE, TRUE);

  //One self locked relais for the 230V gartenpumpe.
  //I used one relais of type.
  SelfLockedRelais.initiate("VAR.Gartenpumpe", 40u, TRUE);

  //Initialize the DHT22 sensor.
  //DHT22 Sensor needs a pull up resisor between SCL and VCC.
  Dth22Sensor.initiate("VAR.Aussentemperatur", 2u, "VAR.AussenFeuchtigkeit");

  //A one wire temp sensor on arduino pin 53.
  TempOneWireSensor.initiate("VAR.TempSensorOneWire", 53u);

  //Ligth intensity element BH1750. Connect VCC with 5V, GND with GND.
  //On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
  //On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
  //See https://www.arduino.cc/en/Reference/Wire for details.
  LightIntensitySensor.initiate("VAR.AussenHelligkeit");


  KeyPad.initiate(4u, 8u, "VAR.KeyPad");

  //All elements registered.
  Serial.println("All elements registered. Starting server");
}
