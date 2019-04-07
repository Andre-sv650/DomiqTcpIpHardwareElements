
#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef STM_VL53L0X_ELEMENT_ENABLED

#ifndef STM_VL53L0X_ELEMENT_H
#define STM_VL53L0X_ELEMENT_H

#include "../datatypes/cpu_datatypes.h"
#include "connected_element_base.h"
#include "../external_libraries/Adafruit_VL53L0X.h"
#include "../HelperFunctions/data_filter_helper.h"

/*
 * Ligth intensity element. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
class STM_VL53L0X_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  STM_VL53L0X_ELEMENT(void);

  /*
 * STM time to flight sensor for ranges. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * If an XSHUT PIN is available. connect it to an GPIO Input with a pull up resistor.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
  void initiate(const String &VarNameInDomiq);

  void background_routine(void);

private:
  Adafruit_VL53L0X lox;
  
  DATA_FILTER_HELPER<Uint16> Filter;
  
  //If the light value is different 100 time, set the value to domiq.
  #define STM_RANGE_VALUE_DIFFERENT 10

  //If the light value minimum difference is greater than 2, a new value is written to domiq.
  #define STM_RANGE_MIN_DIFFERENCE 2
};


#endif //STM_VL53L0X_ELEMENT_H

#endif //STM_VL53L0X_ELEMENT_ENABLED
