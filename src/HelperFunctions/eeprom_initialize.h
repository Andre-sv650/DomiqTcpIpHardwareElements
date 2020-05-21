

#include "datatypes/cpu_datatypes.h"
#include "../external_libraries/eeprom/EEPROMex.h"
#ifndef EEPROM_INITIALIZE_H
#define EEPROM_INITIALIZE_H


class EEPROM_INITIALIZE
{
    public:
    static void initialize(Uint32 Key1, Uint32 Key2);
};


#endif //EEPROM_INITIALIZE_H
