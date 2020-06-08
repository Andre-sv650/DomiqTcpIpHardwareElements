#ifdef ARDUINO_MEGA
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
  Electrical24VPowerSupply.initiate("VAR.Electrical24V", 22u, TRUE);

  PowerSupplyPumpeAndBuchsbaumBeleuchtung.initiate("VAR.BuchsbaumAndPump230V", 23u, TRUE);

  //Initialize the RC switch.
  //RcSwitchElement.initiate("VAR.RcSwitch", 2u);

  //Initialize the relais for garten pumpe.
  RelaisForGartenpumpe.initiate("VAR.GartenPumpe", 24u, 1, TRUE);
  RelaisForGartenpumpe.set_maximum_on_time(MAXIMUM_TIME_FOR_RELAIS);
  

  //Initialize the relais for bewaesserung
  RelaisForGartenSprenger.initiate("VAR.Bewaesserung", 30u, 6u, TRUE, TRUE);
  RelaisForGartenSprenger.set_maximum_on_time(MAXIMUM_TIME_FOR_RELAIS);

  //The external rc switch should turn the gartensprenger on and off.
  //Uint32 RcSwitchCodesForRelais[8] = {5571921, 5571924, 5574993, 5574996, 5575761, 0, 0, 0};
  //RelaisForGartenSprenger.connect_to_internal_rc_switch(&RcSwitchElement.LastReceivedCode, RcSwitchCodesForRelais, RcSwitchCodesForRelais);

  //Initialize the DHT22 sensor.
  //DHT22 Sensor needs a pull up resisor between SCL and VCC.
  Dth22Sensor.initiate("VAR.Aussentemperatur", 40u, "VAR.AussenFeuchtigkeit");

  //A one wire temp sensor on arduino pin 53.
  TempOneWireSensor.initiate("VAR.TempSensorOneWire", 42u);


  //Initialize a S0 element for measurement of the solar collector.
  PhotovoltaicPlantS0Element.initiate("VAR.PhotovoltaicPlant", 2u, INTERRUPT_ELEMENT_DEFAULT_ENTPRELL_TIME_FOR_FAST_IRQS, TRUE);

  //Initialize the element for the rain measurement.
  RainMeasurementElement.initiate("VAR.RegenMenge", 3u, INTERRUPT_ELEMENT_DEFAULT_ENTPRELL_TIME_FOR_SLOW_IRQS, TRUE);


  //Ligth intensity element BH1750. Connect VCC with 5V, GND with GND.
  //On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
  //On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
  //See https://www.arduino.cc/en/Reference/Wire for details.
  LightIntensitySensor.initiate(20u, "VAR.AussenHelligkeit");

  //The STM VL53 range sensor.
  //StmVl53Element.initiate("VAR.StmRangeInMm");

  //Initialize the ultrasonic elements for the drainage.
  Drainage1.initiate("VAR.DrainageWasserstand1", 44u, 45u);
  Drainage2.initiate("VAR.DrainageWasserstand2", 46u, 47u);

  //KeyPad.initiate(4u, 8u, "VAR.KeyPad");

  //All elements registered.
  //Serial.println("All elements registered. Starting server");
}

#endif //ARDUINO_MEGA
