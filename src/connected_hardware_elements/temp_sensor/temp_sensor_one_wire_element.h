

#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_ELEMENT_H
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_H

#include "../Base/connected_element_base.h"
#include "external_libraries/OneWire.h"
#include "../../HelperFunctions/data_filter_helper.h"

/*
 * One temp sensor one wire element
 */
class TEMP_SENSOR_ONE_WIRE_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  TEMP_SENSOR_ONE_WIRE_ELEMENT(void);

  void initiate(const String &VarNameInDomiq, Uint8 Pin);

  void background_routine(void);

private:
  OneWire TempSensor;

  Uint8 InternalState;

  byte type_s;

  byte addr[8];

  Uint32 StartTime;

  DATA_FILTER_HELPER<int16> Filter;

  void background_routine_state_0(void);

  void background_routine_state_2(void);
};


#endif /* TEMP_SENSOR_ONE_WIRE_ELEMENT_H */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED
