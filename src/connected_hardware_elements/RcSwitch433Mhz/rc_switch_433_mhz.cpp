
#include "rc_switch_433_mhz.h"
#include "rc_switch_433_mhz_base_instance.h"
#ifdef RC_SWITCH_433MHZ_ENABLED

//Default constructor.
RC_SWITCH_433MHZ_ELEMENT::RC_SWITCH_433MHZ_ELEMENT()
{
}

/*
 * Initiate the RC switch.
 */
void RC_SWITCH_433MHZ_ELEMENT::initiate(const String &VarNameInDomiq, Uint32 OnCode, Uint32 OffCode)
{
  //Define inputs and outputs
  CONNECTED_ELEMENT_BASE::initiate(VarNameInDomiq);

  this->OnCode = OnCode;

  this->OffCode = OffCode;

  RC_SWITCH_433MHZ_BASE_INSTANCE::register_for_receive(this);
}


void RC_SWITCH_433MHZ_ELEMENT::data_received_from_rc_switch(Uint32 NewCode)
{
  String sampledData = String(NewCode);

  CONNECTED_ELEMENT_BASE::set_new_data_sampled(sampledData);
}


/*Set the data for the switch element.
  Format of the send data is:
  1. Value to be send as 24 bit value.
*/
void RC_SWITCH_433MHZ_ELEMENT::set_data_from_domiq(String &Data)
{
  //Send the data.
  RC_SWITCH_433MHZ_BASE_INSTANCE::send_data(Data);
}

#endif //RC_SWITCH_433MHZ_ENABLED