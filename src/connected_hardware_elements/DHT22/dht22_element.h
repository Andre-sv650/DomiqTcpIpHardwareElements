

#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

#ifndef DHT22_ELEMENT_H
#define DHT22_ELEMENT_H

#include "../Base/connected_element_base.h"
#include "../../external_libraries/DHT/DHT.h"

/*
 * One dht element. Pin selection from left to right. Left from before the sensor.
 * Pin 1: Power 3,3 till 5,5V.
 * Pin 2: Data
 * Pin 3: GND
 * Pin 4: GND
 */
class DHT22_ELEMENT : public CONNECTED_ELEMENT_BASE
{
private:
  DHT MyDht22;

  float32 Temperature;

  float32 Humidity;

  Uint16 Dht22NotAvailableDebugMessageSet;

  String HumidityVarName;

  Uint32 LastReadTime;

public:

  void initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin);

  void initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin, const String &HumidityVarNameInDomiq);

  void background_routine(void);

  void get_sampled_data(String &Result);

  void set_data(String* pValue);

  private:
};

#endif //DHT22_ELEMENT_H

#endif //DHT22_ELEMENT_ENABLED
