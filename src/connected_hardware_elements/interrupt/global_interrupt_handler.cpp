#include <Arduino.h>
#include "../../AllYouNeedIsStartHere/project_defines.h"

#ifdef INTERRUPT_ELEMENT_ENABLED
#define GLOBAL_INTERRUPT_HANDLER_CPP

#include "global_interrupt_handler.h"

GLOBAL_INTERRUPT_HANDLER GlobalInterruptHandler;

GLOBAL_INTERRUPT_HANDLER::GLOBAL_INTERRUPT_HANDLER(void)
{
    GlobalInterruptHandler.RegisteredElements = 0u;
}

void GLOBAL_INTERRUPT_HANDLER::attach_interrupt(INTERRUPT_ELEMENT *pElement)
{
    if (GlobalInterruptHandler.RegisteredElements == 0u)
    {
        attachInterrupt(digitalPinToInterrupt(pElement->Pin), interrupt_routine_for_element0, FALLING);

        GlobalInterruptHandler.pRegisteredElements[0u] = pElement;
    }
    else if (GlobalInterruptHandler.RegisteredElements == 1u)
    {
        attachInterrupt(digitalPinToInterrupt(pElement->Pin), interrupt_routine_for_element1, FALLING);

        GlobalInterruptHandler.pRegisteredElements[1u] = pElement;
    }
    else if (GlobalInterruptHandler.RegisteredElements == 2u)
    {
        attachInterrupt(digitalPinToInterrupt(pElement->Pin), interrupt_routine_for_element2, FALLING);

        GlobalInterruptHandler.pRegisteredElements[2u] = pElement;
    }

    GlobalInterruptHandler.RegisteredElements++;
}

//The interrupt routine for the element 0.
void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element0(void)
{
    if (GlobalInterruptHandler.pRegisteredElements[0] != NULL_PTR)
    {
        GlobalInterruptHandler.pRegisteredElements[0u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element1(void)
{
    if (GlobalInterruptHandler.pRegisteredElements[1] != NULL_PTR)
    {
        GlobalInterruptHandler.pRegisteredElements[1u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element2(void)
{
    if (GlobalInterruptHandler.pRegisteredElements[2] != NULL_PTR)
    {
        GlobalInterruptHandler.pRegisteredElements[2u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element3(void)
{
    if (GlobalInterruptHandler.pRegisteredElements[3] != NULL_PTR)
    {
        GlobalInterruptHandler.pRegisteredElements[3u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element4(void)
{
    if (GlobalInterruptHandler.pRegisteredElements[4] != NULL_PTR)
    {
        GlobalInterruptHandler.pRegisteredElements[4u]->interrupt_routine();
    }
}

#endif //GLOBAL_INTERRUPT_HANDLER_CPP