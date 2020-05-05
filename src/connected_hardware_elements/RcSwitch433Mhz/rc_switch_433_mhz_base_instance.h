
#include "AllYouNeedIsStartHere/project_defines.h"
#ifdef RC_SWITCH_433MHZ_ENABLED

#ifndef RC_SWITCH_433MHZ_BASE_INSTANCE_H
#define RC_SWITCH_433MHZ_BASE_INSTANCE_H

#include "../../datatypes/cpu_datatypes.h"
#include "../Base/connected_element_base.h"
#include "rc_switch_433_mhz.h"
#include "../../external_libraries/RcSwitch/RcSwitch.h"

//24 bit is the default length for sending data to the RC switch.
#define RC_SENDER_CODE_WORD_LENGTH 24

#define RC_SWITCH_433MHZ_BASE_INSTANCE_MAX_ELEMENT_CNT 10

//If a new code was received from the IR control, than this code is send to DOMIQ base.
//After it is send, domiq will send it back to all clients. Avoid that this is send another time, by this receiver.
//Set this time to 0, if you need to send the IR control code once again by this device.
#define RC_SENDER_RECEIVED_TIMEOUT_TIME 2000

/*
 * Connect the RC switch 433Mhz to a interruptable pin.
 */
namespace RC_SWITCH_433MHZ_BASE_INSTANCE
{
  /* The RC switch 433Mhz initialize function.*/
  void initiate(Uint8 InterruptablePin, Uint8 SendPinMustNotBeInteruptable);

  void register_for_receive(RC_SWITCH_433MHZ_ELEMENT *pReceiveInstance);

  void background_routine();

  void send_data(String &Data);

  void data_received();
};


#endif //RC_SWITCH_433MHZ_BASE_INSTANCE_H

#endif //RC_SWITCH_433MHZ_ENABLED
