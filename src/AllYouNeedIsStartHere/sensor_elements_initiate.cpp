
#include "sensor_elements_initiate.h"

/*
* Default constructor.
*/
SENSOR_ELEMENTS_INITIATE::SENSOR_ELEMENTS_INITIATE()
{
}

void SENSOR_ELEMENTS_INITIATE::initiate(void)
{
    //One self locked relais for the 230V gartenpumpe.
  //I used one relais of type.
  SelfLockedRelais.initiate("VAR.Electrical24V", 22u, TRUE);

  //Initialize the relais for garten pumpe.
  RelaisForGartenpumpe.initiate("VAR.GartenPumpe", 24u, 1, TRUE);
  RelaisForGartenpumpe.set_maximum_on_time(MAXIMUM_TIME_FOR_RELAIS);
  
  //Initialize the relais for bewaesserung
  RelaisForGartenSprenger.initiate("VAR.Bewaesserung", 30u, 6u, TRUE, TRUE);
  RelaisForGartenSprenger.set_maximum_on_time(MAXIMUM_TIME_FOR_RELAIS);

  //Initialize the DHT22 sensor.
  //DHT22 Sensor needs a pull up resisor between SCL and VCC.
  Dth22Sensor.initiate("VAR.Aussentemperatur", 40u, "VAR.AussenFeuchtigkeit");

  //A one wire temp sensor on arduino pin 53.
  TempOneWireSensor.initiate("VAR.TempSensorOneWire", 42u);

  //Ligth intensity element BH1750. Connect VCC with 5V, GND with GND.
  //On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
  //On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
  //See https://www.arduino.cc/en/Reference/Wire for details.
  LightIntensitySensor.initiate("VAR.AussenHelligkeit");

  //The STM VL53 range sensor.
  //StmVl53Element.initiate("VAR.StmRangeInMm");

  TankFuellStandLinks.initiate("VAR.TankFuellstandLinks", 44u, 45u);

  TankFuellStandRechts.initiate("VAR.TankFuellstandRechts", 46u, 47u);

  //KeyPad.initiate(4u, 8u, "VAR.KeyPad");

  //All elements registered.
  //Serial.println("All elements registered. Starting server");
}
