
#include "../AllYouNeedIsStartHere/project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED

#include "relais_element.h"
#include "../debug/debug_data.h"
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
}

/*
 * Call the initiate method once for the relays element.
 */
void RELAIS_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed)
{
  this->initiate(VarNameInDomiq, StartPin, PinCount, Reversed, FALSE);
}



void RELAIS_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime)
{
  Uint8 i;
  this->Pin = StartPin;
  this->Reversed = Reversed;
  this->SizeInBits = PinCount;
  this->OnlyOneRelaisAtTime = OnlyOneRelaisAtTime;

  for (i = 0u; i < PinCount; i++)
  {
    //First set the digital output, to avoid that the output is set to on if the pin mode is set first.
    digitalWrite((uint8_t)Pin + i, (uint8_t)Reversed);

    pinMode(Pin + i, OUTPUT); // sets the digital pin as output
  }

  CONNECTED_ELEMENT_BASE::initiate(StartPin, VarNameInDomiq);
}

//Set the data
void RELAIS_ELEMENT::set_data_from_domiq(String &Data)
{
  Uint8 dataAsByte = (Uint8)Data.toInt();

  //Check if the data is 0.
  if(dataAsByte == 0u){
      for (Uint8 i = 0u; i < SizeInBits; i++){
        //Set the new value.
        digitalWrite((uint8_t)Pin + i, (uint8_t)(0x0) ^ Reversed);
      }
  }
  
  //Check if only one element at one time is set.
  if (OnlyOneRelaisAtTime == TRUE)
  {
    //Set all elements to off.
    for (int i = 0u; i < SizeInBits; i++)
    {
      digitalWrite((uint8_t)Pin + i, (uint8_t)(0) ^ Reversed);
    }
  }

  for (Uint8 i = 0u; i < SizeInBits; i++)
  {
    Uint8 mask = 0x1 << i;

    if ((dataAsByte & mask) == mask)
    {
      //Set the new value.
      digitalWrite((uint8_t)Pin + i, (uint8_t)(0x1) ^ Reversed);
      DEBUG_DATA::relais_element_set_data_to_pin((char)(Pin + i));
    }
  }

  DEBUG_DATA::relais_element_set_data_called(String(dataAsByte));
}


String RELAIS_ELEMENT::get_data()
{
  Uint8 result = 0u;

  for (int i = 0u; i < SizeInBits; i++)
  {
    result |= ((digitalRead((uint8_t)(this->Pin + i)) ^ Reversed) << i);
  }

  //Set the data to the base class.
  this->SampledValue = result;
  String resultingString = CONNECTED_ELEMENT_BASE::get_sampled_data();

  DEBUG_DATA::relais_element_get_data_called(resultingString);
  
  return resultingString;
}

#endif //RELAIS_ELEMENT_ENABLED
