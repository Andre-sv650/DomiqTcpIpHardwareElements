

#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef KEYPAD_4_4_ELEMENT_ENABLED

#ifndef KEYPAD_4_4_ELEMENT_H
#define KEYPAD_4_4_ELEMENT_H

#include "../Base/connected_element_base.h"
#include "../../external_libraries/keypad/keypad.h"
/*
 * One keypad 4 * 4 element
 */
class KEYPAD_4_4_ELEMENT : public CONNECTED_ELEMENT_BASE
{
    public:

    void initiate(Uint8 StartPinForRow, Uint8 StartPinForColumn, const String &VarElementNameInDomiq);


    void background_routine(void);

    private:
    Keypad Pad;
};

#endif //KEYPAD_4_4_ELEMENT_H

#endif //KEYPAD_4_4_ELEMENT_ENABLED