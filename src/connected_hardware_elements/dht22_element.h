

#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

#ifndef DHT22_ELEMENT_H
#define DHT22_ELEMENT_H

#include "connected_element_base.h"
#include "../external_libraries/DHT.h"

//Read the data every 5s.
#define DHT22_ELEMENT_READ_DATA_CYCLE 5000u

/*
 * One dht element
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

  String get_sampled_data(void);

  void set_data(String* pValue);

  private:
};

#endif //DHT22_ELEMENT_H

#endif //DHT22_ELEMENT_ENABLED
