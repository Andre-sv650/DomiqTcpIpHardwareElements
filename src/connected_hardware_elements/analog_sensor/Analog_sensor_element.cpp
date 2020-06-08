
#include "analog_sensor_element.h"
#include "Arduino.h"
#ifdef ANALOG_SENSOR_ELEMENT_ENABLED



//Default constructor.
ANALOG_SENSOR_ELEMENT::ANALOG_SENSOR_ELEMENT()
{
}

/*
 * The analog element. Reading the analog value via the analog pin.
 */
void ANALOG_SENSOR_ELEMENT::initiate(Uint8 AnalogPin, const String &VarNameInDomiq)
{
  //Initiate the base element. The analog pin is read.
  CONNECTED_ELEMENT_BASE::initiate(AnalogPin, VarNameInDomiq);

  //Save the last sample time minus the desired sample time. Start sampling a value at startup.
  LastSampleTime = millis() - ANALOG_SENSOR_ELEMENT_SAMPLE_TIME;
}

//Background routine for the analog sensor element.
void ANALOG_SENSOR_ELEMENT::background_routine()
{
    //Check if the time expired.
    if((millis() - LastSampleTime) > ANALOG_SENSOR_ELEMENT_SAMPLE_TIME){
        //Read the analog value.
        int value = analogRead(this->Pin);

        //Check if the value is valid.
        if(value < 0){
          //Value invalid. Try another time and report a debug message.
          Serial.print(F("Analog value was negative for sensor: "));
          Serial.println(this->VarNameInDomiq);
        }
        else{
          //Filter the value.
          Uint16 filteredValue = Filter.filter_value((Uint16)value);

          //Convert it to a string.
          String valueAsString = String(filteredValue);

          #ifdef ANALOG_SENSOR_ELEMENT_DEBUG
          //Write the debug message.
          Serial.print(F("Analog sensor read value: "));
          Serial.println(valueAsString);
          #endif

          //Set the new value to domiq base.
          CONNECTED_ELEMENT_BASE::set_new_data_sampled(valueAsString);
        }

        //Save the last sample time.
        LastSampleTime = millis();
    }
}

#endif //ANALOG_SENSOR_ELEMENT_ENABLED