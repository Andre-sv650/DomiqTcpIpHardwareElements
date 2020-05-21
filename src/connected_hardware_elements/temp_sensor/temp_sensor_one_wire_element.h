

#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_ELEMENT_H
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_H

#include "../Base/connected_element_base.h"
#include "external_libraries/OneWire/OneWire.h"
#include "../../HelperFunctions/data_filter_helper.h"

//State of the conversion.
enum TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_ENUM{

  TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_WAIT = 0,

  TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_START_CONVERSION = 1,

  TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_WAIT_FOR_DATA = 2,

  TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_GET_SAMPLED_DATA = 3
};

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

  TEMP_SENSOR_ONE_WIRE_ELEMENT_STATE_ENUM InternalState;

  byte type_s;

  byte addr[8];

  Uint32 StartTime;

  Uint32 LastSampleTime; //The last sample time in ms.

  DATA_FILTER_HELPER<int16> Filter;

  bool8 background_routine_state_start_conversion(void);

  void background_routine_state_get_sampled_data(void);
};


#endif /* TEMP_SENSOR_ONE_WIRE_ELEMENT_H */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED
