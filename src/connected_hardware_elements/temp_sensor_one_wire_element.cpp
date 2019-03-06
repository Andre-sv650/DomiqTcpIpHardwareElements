
#include "../AllYouNeedIsStartHere/project_defines.h"
#include "../debug/debug_data.h"

#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#define TEMP_SENSOR_ONE_WIRE_ELEMENT_CPP

#include "temp_sensor_one_wire_element.h"

static const String TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE = String("-1000");


TEMP_SENSOR_ONE_WIRE_ELEMENT::TEMP_SENSOR_ONE_WIRE_ELEMENT(void)
{

}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 Pin, OneWire *pTempSensor)
{
    pTempSensor = pTempSensor;
    SampledValue = TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE;

    CONNECTED_ELEMENT_BASE::initiate(Pin, VarNameInDomiq); 

    background_routine(); 
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine(void)
{
    //Get the temperatur and save it.
    //returns the temperature from one DS18S20 in DEG Celsius
    byte data[12];
    byte addr[8];

    if (!pTempSensor->search(addr))
    {
        //no more sensors on chain, reset search
        pTempSensor->reset_search();
        this->SampledValue = TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE;
        return;
    }

    if (OneWire::crc8(addr, 7) != addr[7])
    {
        Serial.println("CRC is not valid!");
        this->SampledValue = TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE;
    }

    if (addr[0] != 0x10 && addr[0] != 0x28)
    {
        Serial.print("Device is not recognized");
        this->SampledValue = TEMP_SENSOR_ONE_WIRE_ELEMENT_DEFAULT_VALUE;
    }

    if(pTempSensor->reset() == 0u){
        Serial.println("No one wire element found");
    }
    pTempSensor->select(addr);
    pTempSensor->write(0x44, 1); // start conversion, with parasite power on at the end

    byte present = pTempSensor->reset();

    if(present == 0u){
        Serial.println("No one wire element found");
    }

    pTempSensor->select(addr);
    pTempSensor->write(0xBE); // Read Scratchpad

    for (int i = 0; i < 9; i++)
    { // we need 9 bytes
        data[i] = pTempSensor->read();
    }

    pTempSensor->reset_search();

    byte MSB = data[1];
    byte LSB = data[0];

    float32 tempRead = ((MSB << 8) | LSB); //using two's compliment
    tempRead = tempRead / 16;
    String newValue = String(tempRead);
    
    CONNECTED_ELEMENT_BASE::set_new_data_sampled(newValue);

    DEBUG_DATA::temp_sensor_one_wire_new_data_sampled(newValue);

    delay(10000);
}

#endif /* TEMP_SENSOR_ONE_WIRE_CPP */