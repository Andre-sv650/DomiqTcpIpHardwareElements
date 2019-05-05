#include <Arduino.h>
#include "../../AllYouNeedIsStartHere/project_defines.h"
#include "../../debug/debug_data.h"

#ifdef INTERRUPT_ELEMENT_ENABLED

#define INTERRUPT_ELEMENT_CPP

#include "interrupt_element.h"
#include "global_interrupt_handler.h"

INTERRUPT_ELEMENT::INTERRUPT_ELEMENT(void)
{
}

void INTERRUPT_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 Pin, Uint8 EntprellTimeInMS)
{
  initiate(VarNameInDomiq, Pin, EntprellTimeInMS, FALSE);
}

void INTERRUPT_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 Pin, Uint8 EntprellTimeInMS, bool8 WithEepromSave)
{
  InterruptCounter = 0u;
  this->WithEepromSave = WithEepromSave;

  if (WithEepromSave == TRUE)
  {
    initialize_eeprom();
  }

  pinMode(Pin, INPUT_PULLUP);
  CONNECTED_ELEMENT_BASE::initiate(Pin, VarNameInDomiq);
  GLOBAL_INTERRUPT_HANDLER::attach_interrupt(this);
}


void INTERRUPT_ELEMENT::initialize_eeprom(void)
{
  EepromAddress = EEPROM.getAddress(sizeof(Uint32));

  //Read the data.
  this->InterruptCounter = EEPROM.readLong(EepromAddress);
  this->NewInterruptCounter = InterruptCounter;

  Serial.println("Data from EEPROM loaded from address: " + String(EepromAddress) + ". Data: " + String(InterruptCounter));

  LastEepromSaveTime = millis();
}


void INTERRUPT_ELEMENT::background_routine(void)
{
  //Check if a new interrupt was set.
  if (InterruptCounter != NewInterruptCounter)
  {
    String interruptNumber = String(InterruptCounter);

    CONNECTED_ELEMENT_BASE::set_new_data_sampled(interruptNumber);

    InterruptCounter = NewInterruptCounter;

    SaveDataToEeprom = TRUE;
  }

  background_routine_save_data_to_eeprom();
}

void INTERRUPT_ELEMENT::background_routine_save_data_to_eeprom(void)
{
  if (WithEepromSave == TRUE)
  {
    if (SaveDataToEeprom == TRUE)
    {
      Uint32 currentTime = millis();

      //Check if it is time to save the new data to the EEPROM.
      if ((currentTime - LastEepromSaveTime) > INTERRUPT_ELEMENT_SAVE_DATA_TO_EEPROM_TIME)
      {
        //Update the data.
        EEPROM.updateLong(EepromAddress, InterruptCounter);

        LastEepromSaveTime = currentTime;
        SaveDataToEeprom = FALSE;

        //The new data was saved to the eeprom.
        Serial.println("Data to EEPROM saved. Address: " + String(EepromAddress) + ". Data: " + String(InterruptCounter));
      }
    }
  }
  else{
    SaveDataToEeprom = FALSE;
  }
}

void INTERRUPT_ELEMENT::interrupt_routine(void)
{
  Uint32 currentTime = millis();

  if (currentTime - EntprellTimer > EntprellTimeInMs)
  {
    //Interrupt detected. Increment the counter.
    NewInterruptCounter++;

    EntprellTimer = currentTime;
  }
}

#endif /* INTERRUPT_ELEMENT_CPP */