

#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

#ifndef DHT22_ELEMENT_H
#define DHT22_ELEMENT_H

#include "connected_element_base.h"
#include "../external_libraries/DHT.h"
/*
 * One dht element
 */
class DHT22_ELEMENT : public CONNECTED_ELEMENT_BASE
{
private:
  DHT MyDht22;

  float32 Temperature;

  float32 Humidity;

  Uint8 Dht22NotAvailableDebugMessageSet;

  String HumidityVarName;

public:

  void initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin);

  void initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin, const String &HumidityVarNameInDomiq);

  void background_routine(void);

  String get_sampled_data(void);

  void set_data(String* pValue);

  private:

  void initiate(void);
};

#endif //DHT22_ELEMENT_H

#endif //DHT22_ELEMENT_ENABLED
