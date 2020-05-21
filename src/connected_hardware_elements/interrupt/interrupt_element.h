/* Interrupt element, connect the interrupt pin to ground to set one interrupt.
   The counter is incremented, if the interrupt pin is released from ground.
*/
#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef INTERRUPT_ELEMENT_ENABLED

#ifndef INTERRUPT_ELEMENT_H
#define INTERRUPT_ELEMENT_H

#include "../Base/connected_element_base.h"
#include "../../external_libraries/eeprom/EEPROMex.h"

//The default entprell zeit for fast IRQs is 100ms.
#define INTERRUPT_ELEMENT_DEFAULT_ENTPRELL_TIME_FOR_FAST_IRQS 100

#define INTERRUPT_ELEMENT_DEFAULT_ENTPRELL_TIME_FOR_SLOW_IRQS 250

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
