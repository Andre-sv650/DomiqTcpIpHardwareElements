

#include "eeprom_initialize.h"




void EEPROM_INITIALIZE::initialize(Uint32 Key1, Uint32 Key2)
{
    bool8 eraseEeprom = TRUE;

    //Check the key in the EEPROM.
    int addressKey1 = EEPROM.getAddress(sizeof(Uint32));
    int addressKey2 = EEPROM.getAddress(sizeof(Uint32));

    //Read the data.
    Uint32 key1InEeprom = EEPROM.readLong(addressKey1);

    if(key1InEeprom == Key1){
        //Read the key 2
        Uint32 key2InEeeprom = EEPROM.readLong(addressKey2);

        if(key2InEeeprom == Key2){
            eraseEeprom = FALSE;
        }
    }

    //Check if the keys are found.
    if(eraseEeprom == TRUE){
        //Keys not found. Erase the full eeprom.
        for(Uint32 i = 0u; i < 100; i++){
            EEPROM.writeByte(i, 0u);
        }

        //Set the keys.
        EEPROM.writeLong(addressKey1, Key1);
        EEPROM.writeLong(addressKey2, Key2);

        Serial.println("EEPROM formatted");
    }

}