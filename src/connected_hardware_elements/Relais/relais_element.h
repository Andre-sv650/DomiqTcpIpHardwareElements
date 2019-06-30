
#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED


#ifndef RELAIS_ELEMENT_H
#define RELAIS_ELEMENT_H

#include "../Base/connected_element_base.h"
/*
 * One relais element of 8 bit
 */
class RELAIS_ELEMENT : public CONNECTED_ELEMENT_BASE
{
protected:
  bool8 Reversed;

  bool8 OnlyOneRelaisAtTime;

  Uint8 SizeInBits;

  Uint32 MaximumOnTimeWithoutChangeInMs;

private:
  Uint32 LastChangeAtMs;

  Uint8 LastRelaisState;

public:
     RELAIS_ELEMENT(void);
     
     void initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed);

     void initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime);

     void set_maximum_on_time(Uint32 MaximumOnTimeInMs);

     String get_data(void);

     void background_routine(void);
     
     void set_data_from_domiq(String &Data);

     void set_data_from_domiq(Uint8 Value);
};

#endif //Relais element

#endif //RELAIS_ELEMENT_ENABLED
