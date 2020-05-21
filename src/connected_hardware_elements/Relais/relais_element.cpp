
#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED

#include "relais_element.h"
#include "../../debug/debug_data.h"
#include "Arduino.h"

/*
 * Constructor
 */
RELAIS_ELEMENT::RELAIS_ELEMENT(void)
{
  Pin = 0u;
  OnlyOneRelaisAtTime = FALSE;
  Reversed = FALSE;
  SizeInBits = 0u;
  MaximumOnTimeWithoutChangeInMs = UINT32_MAX;
  LastRelaisState = 0u;
}

/* Initialize the Relais element.
 * VarNameInDomiq The variable name in Domiq base
 * StartPin The start pin where the relais block is CONNECTED
 * PinCount The number of Relais of the relais element.
 * Reversed Is the relais reversed, this means that setting 5V on the output releases the realais to output state 0.
*/
void RELAIS_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed)
{
  this->initiate(VarNameInDomiq, StartPin, PinCount, Reversed, FALSE);
}

/* Initialize the Relais element.
 * VarNameInDomiq The variable name in Domiq base
 * StartPin The start pin where the relais block is CONNECTED
 * PinCount The number of Relais of the relais element.
 * Reversed Is the relais reversed, this means that setting 5V on the output releases the realais to output state 0.
 * OnlyOneRelaisAtTime It is only allowed that one relais is set at one time.
*/
void RELAIS_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime)
{
  Uint8 i;
  this->Pin = StartPin;
  this->Reversed = Reversed;
  this->SizeInBits = PinCount;
  this->OnlyOneRelaisAtTime = OnlyOneRelaisAtTime;
  pReceivedRcCode = (Uint32*)NULL_PTR;

  for (i = 0u; i < PinCount; i++){
    //First set the digital output, to avoid that the output is set to on if the pin mode is set first.
    digitalWrite((uint8_t)Pin + i, (uint8_t)Reversed);

    pinMode(Pin + i, OUTPUT); // sets the digital pin as output
  }

  CONNECTED_ELEMENT_BASE::initiate(StartPin, VarNameInDomiq);
}

void RELAIS_ELEMENT::set_maximum_on_time(Uint32 MaximumOnTimeInMs)
{
  this->MaximumOnTimeWithoutChangeInMs = MaximumOnTimeInMs;
}


//Connect the relais to the internal rc switch routine.
void RELAIS_ELEMENT::connect_to_internal_rc_switch(Uint32 *pReceivedCode, Uint32 CodesForOn[], Uint32 CodesForOff[])
{
  Uint8 i;
  this->pReceivedRcCode = pReceivedRcCode;
  
  //Copy the codes for the on and off of the relais.
  for(i = 0u; i < SizeInBits; i++){
    this->CodesForOn[i] = CodesForOn[i];
    this->CodesForOff[i] = CodesForOff[i];
  }
}

//The background routine for the relais element.
void RELAIS_ELEMENT::background_routine(void)
{
  //Check if the change time was set by the user.
  if ((LastRelaisState > 0u) && (this->MaximumOnTimeWithoutChangeInMs < UINT32_MAX)){
    //Get the current time.
    if((millis() - LastChangeAtMs) > MaximumOnTimeWithoutChangeInMs){
      //Time expired. Reset
      set_data_from_domiq((Uint8)0u);

      //Report the change also to domiq base.
      this->NewDataSampled = NewDataSampled;
    }
  }
  else{
    LastChangeAtMs = millis();
  }

  //Check if the relais should be set to on or off via a RC code from external.
  if(pReceivedRcCode != NULL_PTR){
    //Check if the code is greater than 0.
    if(*pReceivedRcCode > 0u){
      //Check if one of this relais should be changed.
      Uint8 i;

      for(i = 0u; i < SizeInBits; i++){
        if(*pReceivedRcCode == CodesForOn[i]){
          //Code found, check if this relais is on.
          Uint8 bitFilter = 1u << i;
          Uint8 state = get_data_as_uint8();

          //Check if the state is on.
          if((state & bitFilter) > 0u){
            //State is on. Check if it should be set to off. If this is the same button for on and off.
            if(*pReceivedRcCode == CodesForOff[i]){
              //This is the same button as the one for on. Put the relais to off, mask the bit.
              state = state ^ bitFilter;

              //Set the new state.
              set_data_from_domiq(state);
            }
          }
          else{
            //The state is not on.
            state = state | bitFilter;

            //Set the new state.
            set_data_from_domiq(state);
          }
        }

        //Release the received RC code.
        *pReceivedRcCode = 0u;
        break;
      }
    }
  }
}

//Set the data that was received from domiq base.
void RELAIS_ELEMENT::set_data_from_domiq(String &Data)
{
  Uint8 dataAsByte = (Uint8)Data.toInt();

  this->set_data_from_domiq(dataAsByte);
}


void RELAIS_ELEMENT::set_data_from_domiq(Uint8 Value)
{
  //Check if this is a new value.
  if (Value != LastRelaisState){
    //Check if the data is 0.
    if (Value == 0u){
      for (Uint8 i = 0u; i < SizeInBits; i++){
        //Set the new value.
        digitalWrite((uint8_t)Pin + i, (uint8_t)(0x0u) ^ Reversed);

        //Inform the debugger.
        DEBUG_DATA::relais_element_set_data_to_pin(Pin + i, 0u);
      }
    }

    //Check if only one element at one time is set.
    if (OnlyOneRelaisAtTime == TRUE){
      //Set all elements to off.
      for (int i = 0u; i < SizeInBits; i++){
        digitalWrite((uint8_t)Pin + i, (uint8_t)(0) ^ Reversed);
      }
    }

    for (Uint8 i = 0u; i < SizeInBits; i++){
      Uint8 mask = 0x1u << i;

      if ((Value & mask) == mask){
        //Set the new value.
        digitalWrite((uint8_t)Pin + i, (uint8_t)(0x1u) ^ Reversed);
        DEBUG_DATA::relais_element_set_data_to_pin(Pin + i, 1u);
      }
    }

    LastChangeAtMs = millis();
    LastRelaisState = Value;

    String newValue = String(Value);
    DEBUG_DATA::relais_element_set_data_called(newValue);
  }
}

//Get the data from the relais element.
void RELAIS_ELEMENT::get_data(String &Result)
{
  Uint8 result = get_data_as_uint8();

  //Set the data to the base class.
  this->SampledValue = String(result);
  CONNECTED_ELEMENT_BASE::get_sampled_data(Result);

  DEBUG_DATA::relais_element_get_data_called(Result);
}

//Get the data as uint8.
Uint8 RELAIS_ELEMENT::get_data_as_uint8()
{
  Uint8 result = 0u;

  for (Uint8 i = 0u; i < SizeInBits; i++){
    result |= ((digitalRead((Uint8)(this->Pin + i)) ^ Reversed) << i);
  }

  return result;
}

#endif //RELAIS_ELEMENT_ENABLED
