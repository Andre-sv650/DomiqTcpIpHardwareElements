
#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED


#ifndef RELAIS_ELEMENT_SELF_LOCKED_H
#define RELAIS_ELEMENT_SELF_LOCKED_H

#include "relais_element.h"

  enum RELAIS_ELEMENT_SELF_LOCK_STATE{
    RELAIS_ELEMENT_SELF_LOCK_STATE_OFF = 0,

    RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_ON = 100,

    RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_ON_IN_PROGRESS = 101,


    RELAIS_ELEMENT_SELF_LOCK_STATE_ON = 1,

    RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_TO_OFF = 200, 

    RELAIS_ELEMENT_SELF_LOCK_STATE_SWITCH_OFF_IN_PROGRESS = 201
  };


/*
 * One relais element of 8 bit
 */
class RELAIS_ELEMENT_SELF_LOCKED : public RELAIS_ELEMENT
{
private:

  RELAIS_ELEMENT_SELF_LOCK_STATE State;

  RELAIS_ELEMENT_SELF_LOCK_STATE NextState;

  //The state was set at the millisecond
  Uint32 SetAtTime;

  bool8 ThisSelfLockedRelaisInProgress;

public:
     RELAIS_ELEMENT_SELF_LOCKED(void);
     
     void initiate(const String &VarNameInDomiq, Uint8 Pin, bool8 Reversed);

     void background_routine(void);

     void get_data(String &Result);
     
     void set_data_from_domiq(String &Data);
};

#endif //Relais element self locked

#endif //RELAIS_ELEMENT_ENABLED
