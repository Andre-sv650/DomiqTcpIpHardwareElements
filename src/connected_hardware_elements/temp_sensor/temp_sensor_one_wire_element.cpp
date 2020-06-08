
#include "../../AllYouNeedIsStartHere/project_defines.h"

#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_CPP

#include "temp_sensor_one_wire_element.h"

static const String TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE = String("-1000");


//Constructor.
TEMP_SENSOR_ONE_WIRE_ELEMENT::TEMP_SENSOR_ONE_WIRE_ELEMENT(void)
{
}

void TEMP_SENSOR_ONE_WIRE_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 Pin)
{
  //Initialize the temp sensor.
  TempSensor = OneWire();
  TempSensor.begin(Pin);
  SampledValue = TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE;

  CONNECTED_ELEMENT_BASE::initiate(Pin, VarNameInDomiq);

  //After startup, sample the first data directly.
  InternalState = TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_START_CONVERSION;

  //Set the last sample time to the current time minus the difference.
  //Sample the new value at startup.
  LastSampleTime = 0u;
}

void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine(void)
{
  if(InternalState == TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_WAIT){
    //Check if the next sample time is reached.
    if(millis() - LastSampleTime > TEMP_SENSOR_ONE_WIRE_ELEMENT_SAMPLE_TIME){
      //Time limit reached. Sample one temp sensor value.
      InternalState = TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_START_CONVERSION;
    }
  }
  else if (InternalState == TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_START_CONVERSION)
  {
    background_routine_state_start_conversion();

    InternalState = TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_WAIT_FOR_DATA;
  }
  else if (InternalState == TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_WAIT_FOR_DATA)
  {
    // delay(1000);     // maybe 750ms is enough, maybe not. 1000ms are always enough.
    // we might do a ds.depower() here, but the reset will take care of it.
    if ((millis() - StartTime) > 1000u)
    {
      InternalState = TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_GET_SAMPLED_DATA;
    }
  }
  else
  {
    background_routine_state_get_sampled_data();

    //Reset the internal state.
    InternalState = TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_WAIT;
  }
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine_state_start_conversion()
{  
  if (!TempSensor.search(addr)){
    #ifdef DEBUG_TEMP_SENSOR_ONE_WIRE
    Serial.println(F("No more addresses."));
    #endif

    TempSensor.reset_search();
    return;
  }

  #ifdef DEBUG_TEMP_SENSOR_ONE_WIRE
  //Serial.print("ROM =");
  for (i = 0; i < 8; i++){
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }
  #endif

  if (OneWire::crc8(addr, 7) != addr[7]){
    Serial.println(F("Temp sensor one wire. CRC is invalid!"));
    return;
  }

  // the first ROM byte indicates which chip
  switch (addr[0]){
  case 0x10:
    #ifdef DEBUG_TEMP_SENSOR_ONE_WIRE
    Serial.println(F("  Chip = DS18S20"));  // or old DS1820
    #endif
    type_s = 1;
    break;
  case 0x28:
    #ifdef DEBUG_TEMP_SENSOR_ONE_WIRE
    Serial.println(F("  Chip = DS18B20"));
    #endif
    type_s = 0;
    break;
  case 0x22:
    #ifdef DEBUG_TEMP_SENSOR_ONE_WIRE
    Serial.println(F("  Chip = DS1822"));
    #endif
    type_s = 0;
    break;
  default:
    //Serial.println("Device is not a DS18x20 family device.");
    return;
  }

  TempSensor.reset();
  TempSensor.select(addr);
  TempSensor.write(0x44, 1); // start conversion, with parasite power on at the end

  //Save the start time of the conversion.
  StartTime = millis();
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine_state_get_sampled_data()
{
  Uint8 i;
  int16 raw;
  byte data[12];
  float celsius;
  String newSampledData;

  // we might do a ds.depower() here, but the reset will take care of it.
  TempSensor.reset();
  TempSensor.select(addr);
  TempSensor.write(0xBE); // Read Scratchpad

  for (i = 0; i < 9; i++)
  { // we need 9 bytes
    data[i] = TempSensor.read();

    #ifdef DEBUG_TEMP_SENSOR_ONE_WIRE
    Serial.print(F("Temp sensor has read data. New data: "));
    Serial.println(data[i], HEX);
    #endif
  }

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

  raw = Filter.filter_value(raw);

  celsius = (float)raw / 16.0;

  newSampledData = String(celsius);

  CONNECTED_ELEMENT_BASE::set_new_data_sampled(newSampledData);

  //Save the sample time.
  LastSampleTime = millis();
}

#endif /* TEMP_SENSOR_ONE_WIRE_CPP */