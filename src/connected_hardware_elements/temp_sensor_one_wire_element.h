

#include "../AllYouNeedIsStartHere/project_defines.h"
#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_ELEMENT_H
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_H

#include "connected_element_base.h"
#include "external_libraries/OneWire.h"

/*
 * One temp sensor one wire element
 */
class TEMP_SENSOR_ONE_WIRE_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  TEMP_SENSOR_ONE_WIRE_ELEMENT(void);

  void initiate(const String &VarNameInDomiq, Uint8 Pin, OneWire *pTempSensor);

  void background_routine(void);

private:
  OneWire *pTempSensor;
};


#endif /* TEMP_SENSOR_ONE_WIRE_ELEMENT_H */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED
