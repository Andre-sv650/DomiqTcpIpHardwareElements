#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef INTERRUPT_ELEMENT_ENABLED

#ifndef INTERRUPT_ELEMENT_H
#define INTERRUPT_ELEMENT_H

#include "../Base/connected_element_base.h"
#include "../../external_libraries/eeprom/EEPROMex.h"

/*
 * Interrupt element
 */
class INTERRUPT_ELEMENT : public CONNECTED_ELEMENT_BASE
{
public:
  INTERRUPT_ELEMENT(void);

  void initiate(const String &VarNameInDomiq, Uint8 Pin, Uint8 EntprellTimeInMS);

  void initiate(const String &VarNameInDomiq, Uint8 Pin, Uint8 EntprellTimeInMS, bool8 WithEepromSave);

  void background_routine(void);

  void interrupt_routine(void);

private:

  void initialize_eeprom(void);

  void background_routine_save_data_to_eeprom(void);

  Uint32 EntprellTimer;

  bool8 WithEepromSave;

  int EepromAddress;

  Uint32 InterruptCounter;

  volatile Uint32 NewInterruptCounter;

  Uint32 LastEepromSaveTime;

  bool8 SaveDataToEeprom;

  Uint8 EntprellTimeInMs;
};


#endif /* INTERRUPT_ELEMENT_H */

#endif //INTERRUPT_ELEMENT_ENABLED
