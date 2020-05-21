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

/*
* Attach one interrupt to the global interrupt handler.
*/
void GLOBAL_INTERRUPT_HANDLER::attach_interrupt(INTERRUPT_ELEMENT *pElement)
{
    int32 interruptNumber = digitalPinToInterrupt(pElement->Pin);

    if(interruptNumber == NOT_AN_INTERRUPT){
        //Invalid pin.
        Serial.println(F("IRQ not registered, error"));
    }
    else {
        if (GlobalInterruptHandler.RegisteredElements == 0u){
            attachInterrupt((uint8_t)interruptNumber, interrupt_routine_for_element0, RISING);

            GlobalInterruptHandler.pRegisteredElements[0u] = pElement;
        }
        else if (GlobalInterruptHandler.RegisteredElements == 1u){
            attachInterrupt((uint8_t)interruptNumber, interrupt_routine_for_element1, RISING);

            GlobalInterruptHandler.pRegisteredElements[1u] = pElement;
        }
        else if (GlobalInterruptHandler.RegisteredElements == 2u){
            attachInterrupt((uint8_t)interruptNumber, interrupt_routine_for_element2, RISING);

            GlobalInterruptHandler.pRegisteredElements[2u] = pElement;
        }
        else if (GlobalInterruptHandler.RegisteredElements == 3u){
            attachInterrupt((uint8_t)interruptNumber, interrupt_routine_for_element3, RISING);

            GlobalInterruptHandler.pRegisteredElements[3u] = pElement;
        }
        else if (GlobalInterruptHandler.RegisteredElements == 4u){
            attachInterrupt((uint8_t)interruptNumber, interrupt_routine_for_element4, FALLING);

            GlobalInterruptHandler.pRegisteredElements[4u] = pElement;
        }
        else{
            Serial.print(F("No IRQ routine free for: "));
            Serial.println(pElement->Pin);
        }

        //Increment the registered elements counter.
        GlobalInterruptHandler.RegisteredElements++;

        #ifdef DEBUG_INTERRUPT_ELEMENT
            Serial.print(F("IRQ installed for Pin: "));
            Serial.println(pElement->Pin);
        #endif
    }
}

//The interrupt routine for the element 0.
void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element0(void)
{
    #ifdef DEBUG_INTERRUPT_ELEMENT
    Serial.println(GlobalInterruptHandler.DebugMessage + "0");
    #endif

    if (GlobalInterruptHandler.pRegisteredElements[0] != NULL_PTR){
        GlobalInterruptHandler.pRegisteredElements[0u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element1(void)
{
    #ifdef DEBUG_INTERRUPT_ELEMENT
    Serial.println(GlobalInterruptHandler.DebugMessage + "1");
    #endif

    if (GlobalInterruptHandler.pRegisteredElements[1] != NULL_PTR){
        GlobalInterruptHandler.pRegisteredElements[1u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element2(void)
{
    #ifdef DEBUG_INTERRUPT_ELEMENT
    Serial.println(GlobalInterruptHandler.DebugMessage + "2");
    #endif

    if (GlobalInterruptHandler.pRegisteredElements[2] != NULL_PTR){
        GlobalInterruptHandler.pRegisteredElements[2u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element3(void)
{
    #ifdef DEBUG_INTERRUPT_ELEMENT
    Serial.println(GlobalInterruptHandler.DebugMessage + "3");
    #endif
    
    if (GlobalInterruptHandler.pRegisteredElements[3] != NULL_PTR){
        GlobalInterruptHandler.pRegisteredElements[3u]->interrupt_routine();
    }
}

void GLOBAL_INTERRUPT_HANDLER::interrupt_routine_for_element4(void)
{
    #ifdef DEBUG_INTERRUPT_ELEMENT
    Serial.println(GlobalInterruptHandler.DebugMessage + "4");
    #endif
    
    if (GlobalInterruptHandler.pRegisteredElements[4] != NULL_PTR){
        GlobalInterruptHandler.pRegisteredElements[4u]->interrupt_routine();
    }
}

#endif //GLOBAL_INTERRUPT_HANDLER_CPP