
#include "../../AllYouNeedIsStartHere/project_defines.h"

#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_CPP

#include "temp_sensor_one_wire_element.h"

static const String TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE = String("-1000");

TEMP_SENSOR_ONE_WIRE_ELEMENT::TEMP_SENSOR_ONE_WIRE_ELEMENT(void)
{
}

void TEMP_SENSOR_ONE_WIRE_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 Pin)
{
  TempSensor = OneWire();
  TempSensor.begin(Pin);
  SampledValue = TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE;

  CONNECTED_ELEMENT_BASE::initiate(Pin, VarNameInDomiq);

  InternalState = 0u;

  background_routine();
}

void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine(void)
{
  if (InternalState == 0)
  {
    background_routine_state_0();

    StartTime = millis();

    InternalState = 1u;
  }
  else if (InternalState == 1u)
  {
    Uint32 timeDifference = StartTime - millis();

    if (timeDifference > 1000)
    {
      // delay(1000);     // maybe 750ms is enough, maybe not
      // we might do a ds.depower() here, but the reset will take care of it.
      InternalState = 2u;
    }
  }
  else
  {
    background_routine_state_2();

    InternalState = 0u;
  }
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine_state_0()
{
  Uint8 i;
  
  if (!TempSensor.search(addr))
  {
    //Serial.println("No more addresses.");
    TempSensor.reset_search();
    return;
  }

  //Serial.print("ROM =");
  for (i = 0; i < 8; i++)
  {
    //Serial.write(' ');
    //Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7])
  {
    Serial.println("CRC is not valid!");
    return;
  }
  //Serial.println();

  // the first ROM byte indicates which chip
  switch (addr[0])
  {
  case 0x10:
    //Serial.println("  Chip = DS18S20");  // or old DS1820
    type_s = 1;
    break;
  case 0x28:
    //Serial.println("  Chip = DS18B20");
    type_s = 0;
    break;
  case 0x22:
    //Serial.println("  Chip = DS1822");
    type_s = 0;
    break;
  default:
    //Serial.println("Device is not a DS18x20 family device.");
    return;
  }

  TempSensor.reset();
  TempSensor.select(addr);
  TempSensor.write(0x44, 1); // start conversion, with parasite power on at the end
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine_state_2()
{
  Uint8 i;
  int16 raw;
  byte present = 0;
  byte data[12];
  float celsius;
  String newSampledData;

  //delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  present = TempSensor.reset();
  TempSensor.select(addr);
  TempSensor.write(0xBE); // Read Scratchpad

  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for (i = 0; i < 9; i++)
  { // we need 9 bytes
    data[i] = TempSensor.read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  raw = (data[1] << 8) | data[0];
  if (type_s)
  {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10)
    {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  }
  else
  {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00)
      raw = raw & ~7; // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20)
      raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40)
      raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }

  raw = Filter.filter_value(raw , 10, 10);

  celsius = (float)raw / 16.0;

  newSampledData = String(celsius);

  CONNECTED_ELEMENT_BASE::set_new_data_sampled(newSampledData);
}

#endif /* TEMP_SENSOR_ONE_WIRE_CPP */