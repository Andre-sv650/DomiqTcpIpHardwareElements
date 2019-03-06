
#include "../AllYouNeedIsStartHere/project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED


#ifndef RELAIS_ELEMENT_H
#define RELAIS_ELEMENT_H

#include "connected_element_base.h"
/*
 * One relais element of 8 bit
 */
class RELAIS_ELEMENT : public CONNECTED_ELEMENT_BASE
{
private:
  bool8 Reversed;

  bool8 OnlyOneRelaisAtTime;

  Uint8 SizeInBits;

public:
     RELAIS_ELEMENT(void);
     
     void initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed);

     void initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime);

     String get_data(void);
     
     void set_data_from_domiq(String &Data);
};

#endif //Relais element

#endif //RELAIS_ELEMENT_ENABLED
