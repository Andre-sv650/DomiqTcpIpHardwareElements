#include "../AllYouNeedIsStartHere/project_defines.h"

//Check if arduino is used. In case of node mcu there is no watchdog available.
#ifdef NODEMCU
#else
#include <avr/wdt.h>
#endif //NODEMCU

void watchdog_enable(void)
{
    #ifdef NODEMCU

    #else
    // Watchdog auf 1 s stellen
    wdt_enable(WDTO_1S);

    #endif
}


void watchdog_reset_time(void)
{
  #ifdef NODEMCU

  #else
  wdt_reset();

  #endif
}