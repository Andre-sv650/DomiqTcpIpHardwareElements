
#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef BHI_1750FVI_LIGHT_INTENSITY_ENABLED

#ifndef BHI_1750FVI_LIGHT_INTENSITY_H
#define BHI_1750FVI_LIGHT_INTENSITY_H

#include "../../datatypes/cpu_datatypes.h"
#include "../Base/connected_element_base.h"
#include "../../external_libraries/BH1750/ErriezBH1750.h"
#include "../../HelperFunctions/data_filter_helper.h"

/*
 * Ligth intensity element. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
class BHI_1750FVI_LIGHT_INTENSITY : public CONNECTED_ELEMENT_BASE
{
public:
  BHI_1750FVI_LIGHT_INTENSITY(void);

  /*
 * Ligth intensity element. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
  void initiate(const String &VarNameInDomiq);

  void background_routine(void);

private:
  DATA_FILTER_HELPER<Uint16> Filter;
  
  //If the light value is different 100 time, set the value to domiq.
  #define LIGHT_VALUE_DIFFERENT 10

  //If the light value minimum difference is greater than 2, a new value is written to domiq.
  #define LIGHT_VALUE_MIN_DIFFERENCE 2

  Uint16 LightIntensityValue;

  Uint8  LightValueDifferentCounter;
};


#endif //BHI_1750FVI_LIGHT_INTENSITY_H

#endif //BHI_1750FVI_LIGHT_INTENSITY_ENABLED
