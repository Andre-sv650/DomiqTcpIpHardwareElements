
#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED

#include "relais_element_self_locked.h"
#include "Arduino.h"

/*
 * Constructor
 */
RELAIS_ELEMENT_SELF_LOCKED::RELAIS_ELEMENT_SELF_LOCKED(void)
{

}

/* Initialize the Relais element for one self locked relais
 * VarNameInDomiq The variable name in Domiq base
 * StartPin The start pin where the relais block is CONNECTED
 * PinCount The number of Relais of the relais element.
 * Reversed Is the relais reversed, this means that setting 5V on the output releases the realais to output state 0.
 * OnlyOneRelaisAtTime It is only allowed that one relais is set at one time.
*/
void RELAIS_ELEMENT_SELF_LOCKED::initiate(const String &VarNameInDomiq, Uint8 Pin, bool8 Reversed)
{
  RELAIS_ELEMENT::initiate(VarNameInDomiq, Pin, 1u, Reversed, FALSE);
}

//Set the data that was received from domiq base.
void RELAIS_ELEMENT_SELF_LOCKED::set_data_from_domiq(String &Data)
{
  Uint8 dataAsByte = (Uint8)Data.toInt();

  //Set the output state to ON.
  RELAIS_ELEMENT::set_data_from_domiq(1u);

  //Save the set time.
  SetAtTime = millis();

  //Check which state should be set.
  if(dataAsByte == 0u){
    if(State == RELAIS_ELEMENT_SELF_LOCK_STATE_ON){
      //Switch it to off.
      State = RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_TO_OFF;
    }
  }
  else{
    if(State == RELAIS_ELEMENT_SELF_LOCK_STATE_OFF){
      State = RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_ON;
    }
  }
}

//The background routine
void RELAIS_ELEMENT_SELF_LOCKED::background_routine()
{
  //Check if the self lock state was set.
  if(State == RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_ON){
    //Check if the milli seconds is done, normally the relais needs not more than 80ms for setting. Set 500ms for default.
    Uint32 timeDiff = millis() - SetAtTime;

    if(timeDiff > RELAIS_ELEMENT_SELF_LOCKED_RELAIS_ON_OFF_TIME){
      //Switch the output off.
      Uint8 dataAsByte = 0u;

      RELAIS_ELEMENT::set_data_from_domiq(dataAsByte);

      //Reset the self lock state.
      State = RELAIS_ELEMENT_SELF_LOCK_STATE_ON;
    }
  }
  else if(State == RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_TO_OFF){
    //Check if the milli seconds is done, normally the relais needs not more than 80ms for setting. Set 500ms for default.
    Uint32 timeDiff = millis() - SetAtTime;

    if(timeDiff > RELAIS_ELEMENT_SELF_LOCKED_RELAIS_ON_OFF_TIME){
      //Switch the output off.
      Uint8 dataAsByte = 0u;

      RELAIS_ELEMENT::set_data_from_domiq(dataAsByte);

      //Reset the self lock state.
      State = RELAIS_ELEMENT_SELF_LOCK_STATE_OFF;
    }
  }
}


//Get the data from the relais element.
String RELAIS_ELEMENT_SELF_LOCKED::get_data()
{
  //New data was received. Generate the domiq string.
  return generate_domiq_string((Uint8) State);
}

#endif //RELAIS_ELEMENT_ENABLED
