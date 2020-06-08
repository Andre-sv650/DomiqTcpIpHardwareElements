
#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef ANALOG_SENSOR_ELEMENT_ENABLED

#ifndef ANALOG_SENSOR_ELEMENT_H
#define ANALOG_SENSOR_ELEMENT_H

#include "../../datatypes/cpu_datatypes.h"
#include "../Base/connected_element_base.h"
#include "../../HelperFunctions/data_filter_helper.h"

/*
 * Uses one analog pin to read for example the analog moisture value.
 */
class ANALOG_SENSOR_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  ANALOG_SENSOR_ELEMENT(void);

  /*
   *Analog element, reading the analog value of the analog pin.
   */
  void initiate(Uint8 AnalogPin, const String &VarNameInDomiq);

  void background_routine(void);

private:
  DATA_FILTER_HELPER<Uint16> Filter;

  Uint16 MoistureValue;

  Uint32 LastSampleTime;
};


#endif //ANALOG_SENSOR_ELEMENT_H

#endif //ANALOG_SENSOR_ELEMENT_ENABLE
