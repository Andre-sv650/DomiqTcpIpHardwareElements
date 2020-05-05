
#include "rc_switch_433_mhz_base_instance.h"
#ifdef RC_SWITCH_433MHZ_ENABLED

/*
 * Connect the RC switch 433Mhz to a interruptable pin.
 */
namespace RC_SWITCH_433MHZ_BASE_INSTANCE
{
  //Variables
  static RCSwitch RcSwitchLibInstance;

  static RC_SWITCH_433MHZ_ELEMENT *pRegisteredCodes[RC_SWITCH_433MHZ_BASE_INSTANCE_MAX_ELEMENT_CNT];

  static Uint8 RegisteredElementsCnt;

  //The code that was received at last from the IR control.
  static Uint32 LastReceivedCode;

  //The time at which new data was received from the IR control. This time is in milli seconds.
  static Uint32 ReceivedDataTime;

  static bool8 WaitTillTimeIsOver;


/*
 * Initiate the RC switch.
 */
void initiate(Uint8 InterruptablePin, Uint8 SendPinMustNotBeInteruptable)
{
  LastReceivedCode = 0u;
  ReceivedDataTime = 0u;
  WaitTillTimeIsOver = FALSE;

  RegisteredElementsCnt = 0u;
  
  RcSwitchLibInstance.enableReceive(InterruptablePin);  //This should be a interrupt pin.

  RcSwitchLibInstance.enableTransmit(SendPinMustNotBeInteruptable);
}


//Register for receiving data.
void register_for_receive(RC_SWITCH_433MHZ_ELEMENT *pReceiveInstance)
{
  //Check if the maximum number is reached.
  if(RegisteredElementsCnt < RC_SWITCH_433MHZ_BASE_INSTANCE_MAX_ELEMENT_CNT){
    //Register the on code.
    pRegisteredCodes[RegisteredElementsCnt] = pReceiveInstance;

    RegisteredElementsCnt++;
  }
  else{
    Serial.println("RC switch instance could not be registered, too many elements");
  }
}

//Background routine for the light intensity.
void background_routine()
{
  //Check if new data is available.
  if (RcSwitchLibInstance.available()) {
    LastReceivedCode = RcSwitchLibInstance.getReceivedValue();
    String receivedValueAsString = String(LastReceivedCode);

    #ifdef DEBUG_RC_SWITCH_ELEMENT
    Serial.print(F("New value incoming from RC Switch: "));
    Serial.print(LastReceivedCode); 
    Serial.print(F(". Length in BIT: "));
    Serial.println(RcSwitchLibInstance.getReceivedBitlength());
    //Serial.print(RcSwitchLibInstance.getReceivedDelay());
    //Serial.println(RcSwitchLibInstance.getReceivedProtocol());
    #endif //DEBUG_RC_SWITCH_ELEMENT

    RcSwitchLibInstance.resetAvailable();

    //Save the time at which the last value was received.
    ReceivedDataTime = millis();

    //The same data should not be send again by this device.
    WaitTillTimeIsOver = TRUE;

    //Call the data received function of this element.
    data_received();
  }
}


void data_received(void)
{
  Uint8 i;

  for(i = 0u; i < RegisteredElementsCnt; i++){
    //Check if the code matches.
    if(LastReceivedCode == pRegisteredCodes[i]->OnCode){
      //Element found.
      pRegisteredCodes[i]->data_received_from_rc_switch(pRegisteredCodes[i]->OnCode);

      break;
    }
    else if(LastReceivedCode == pRegisteredCodes[i]->OffCode){
      //Element found.
      pRegisteredCodes[i]->data_received_from_rc_switch(pRegisteredCodes[i]->OffCode);

      break;
    }
  }
}

/*Set the data for the switch element.
  Format of the send data is:
  1. Value to be send as 24 bit value.
*/
void send_data(String &Data)
{
  //Get the 32 bit value out of the string from domiq.
  Uint32 uint32Data = (Uint32)Data.toInt();
  bool8 sendData = FALSE;

  if(LastReceivedCode != uint32Data){
    sendData = TRUE;
  }
  else{
    //Check if the time has to be waited for.
    if(WaitTillTimeIsOver == TRUE){
      //Ok time is over, wait data done.
      WaitTillTimeIsOver = FALSE;
    }
    else{
      sendData = TRUE;
    }
  }

  if(sendData == TRUE){
    #ifdef DEBUG_RC_SWITCH_ELEMENT
    Serial.print("New Rc switch value is send: ");
    Serial.println(uint32Data);

    #endif //DEBUG_RC_SWITCH_ELEMENT

    //Send the data that was received from DOMIQ base. This data is not received by this instance.
    RcSwitchLibInstance.send(uint32Data, RC_SENDER_CODE_WORD_LENGTH);
  }
}

} // End of name space RC_SWITCH_433MHZ_BASE_INSTANCE

#endif //RC_SWITCH_433MHZ_ENABLED