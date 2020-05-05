
#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef RC_SWITCH_433MHZ_ENABLED

#ifndef RC_SWITCH_433MHZ_H
#define RC_SWITCH_433MHZ_H

#include "../../datatypes/cpu_datatypes.h"
#include "../Base/connected_element_base.h"
#include "../../external_libraries/RcSwitch/RcSwitch.h"
#include "../../HelperFunctions/data_filter_helper.h"

//24 bit is the default length for sending data to the RC switch.
#define RC_SENDER_CODE_WORD_LENGTH 24

/*
 * Connect the RC switch 433Mhz to a interruptable pin.
 */
class RC_SWITCH_433MHZ_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  RC_SWITCH_433MHZ_ELEMENT(void);

  /* The RC switch 433Mhz initialize function.
 */
  void initiate(const String &VarNameInDomiq, Uint32 OnCode, Uint32 OffCode);

  void data_received_from_rc_switch(Uint32 NewCode);

  void set_data_from_domiq(String &Data);

  Uint32 OnCode;

  Uint32 OffCode;
};


#endif //RC_SWITCH_433MHZ_H

#endif //RC_SWITCH_433MHZ_ENABLED
