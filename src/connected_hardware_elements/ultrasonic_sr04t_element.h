
#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef ULTRASONIC_SR04T_ELEMENT_ENABLED

#ifndef ULTRASONIC_SR04T_ELEMENT_H
#define ULTRASONIC_SR04T_ELEMENT_H

#include "../datatypes/cpu_datatypes.h"
#include "connected_element_base.h"
#include "../external_libraries/ErriezBH1750.h"
#include "../HelperFunctions/data_filter_helper.h"

//If the value is 10 times the same, the value can be used. This avoids wrong measurements.
#define ULTRASONIC_SR04T_ELEMENT_FILTER_VALUE 10u

/*
 * Ultra sonic SR04T element. Connect VCC with 5V, GND with GND.
 */
class ULTRASONIC_SR04T_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  ULTRASONIC_SR04T_ELEMENT(void);

  /*
 * Ligth intensity element. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
  void initiate(const String &VarNameInDomiq, Uint8 TriggerPin, Uint8 EchoPin);

  void background_routine(void);

private:
  DATA_FILTER_HELPER<Uint16> Filter;

  Uint8 EchoPin;
};


#endif //ULTRASONIC_SR04T_ELEMENT_H

#endif //ULTRASONIC_SR04T_ELEMENT_ENABLED
