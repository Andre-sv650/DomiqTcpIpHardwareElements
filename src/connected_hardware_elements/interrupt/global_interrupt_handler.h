#include "../../AllYouNeedIsStartHere/project_defines.h"
#ifdef INTERRUPT_ELEMENT_ENABLED

#ifndef GLOBAL_INTERRUPT_HANDLER_H
#define GLOBAL_INTERRUPT_HANDLER_H

#include "interrupt_element.h"

/*
 * Interrupt handler
 */
class GLOBAL_INTERRUPT_HANDLER
{
    public:

    INTERRUPT_ELEMENT *pRegisteredElements[MaximumNumberOfInterrupts];
    Uint8 RegisteredElements;

    GLOBAL_INTERRUPT_HANDLER();

    static void attach_interrupt(INTERRUPT_ELEMENT *pElement);

    static void interrupt_routine_for_element0(void);

    static void interrupt_routine_for_element1(void);

    static void interrupt_routine_for_element2(void);

    static void interrupt_routine_for_element3(void);

    static void interrupt_routine_for_element4(void);

    private:

    const String DebugMessage = "IRQ called for IRQ element ";
};


#endif //global_interrupt_handler.h

#endif //INTERRUPT_ELEMENT_ENABLED