
#include "bhi1750fvi_light_intensity.h"
#ifdef BHI_1750FVI_LIGHT_INTENSITY_ENABLED

// Depends on the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// See guide for details on sensor wiring and usage:
// https://learn.adafruit.com/dht/overview

//#include "../debug/debug_data.h"

// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 Sensor(LOW);

//Default constructor.
BHI_1750FVI_LIGHT_INTENSITY::BHI_1750FVI_LIGHT_INTENSITY()
{
}

/*
 * Ligth intensity element. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
void BHI_1750FVI_LIGHT_INTENSITY::initiate(Uint8 SdaPin, const String &VarNameInDomiq)
{
  //Initialize I2C bus
  Wire.begin();

  //Initialize sensor in continues mode, high 0.5 lx resolution. 180ms conversion time.
  Sensor.begin(ModeContinuous, ResolutionHigh);
  
  //Sample the first value.
  StateMachine = BHI_1750FVI_LIGHT_INTENSITY_STATE_START_CONVERSION;

  //Initiate the base element. Root pin is pin 20, this is SDA on I2C
  CONNECTED_ELEMENT_BASE::initiate(SdaPin, VarNameInDomiq);
}

//Background routine for the light intensity.
void BHI_1750FVI_LIGHT_INTENSITY::background_routine()
{
  if(StateMachine == BHI_1750FVI_LIGHT_INTENSITY_STATE_WAIT){
    //Check if the time expired.
    if(millis() - LastSampleTime > BHI_1750FVI_LIGHT_INTENSITY_SAMPLE_TIME){
      //Start the conversion.
      StateMachine = BHI_1750FVI_LIGHT_INTENSITY_STATE_START_CONVERSION;
    }
  }
  else if(StateMachine == BHI_1750FVI_LIGHT_INTENSITY_STATE_START_CONVERSION){
    #ifdef DEBUG_LIGHT_INTENSITY_ELEMENT
    Serial.print(F("Light intensity started for element: "));
    Serial.println(VarNameInDomiq);
    #endif

    //Start a new conversion.
    Sensor.startConversion();

    //Wait for the data.
    StateMachine = BHI_1750FVI_LIGHT_INTENSITY_STATE_WAIT_FOR_DATA;

    //Get the current time for sampling the data.
    LastSampleTime = millis();
  }
  else{
    //Check if the conversion is done.
    if(Sensor.isConversionCompleted() == TRUE){
      // Read light level from the sensor.
      Uint16 light = Sensor.read();

      //Filter the value. Do not use any difference.
      Uint16 newLight = Filter.filter_value(light);
      
      //Calculate the new lightning value. This is from the example at 
      //https://github.com/Erriez/ErriezBH1750/blob/master/examples/OneTimeMode/BH1750OneTimeHighResolution/BH1750OneTimeHighResolution.ino
      String newLightValue = String(newLight / 2) + "." + String(newLight % 10);

      //Set the sampled data.
      CONNECTED_ELEMENT_BASE::set_new_data_sampled(newLightValue);

      //Save the current time.
      LastSampleTime = millis();

      #ifdef DEBUG_LIGHT_INTENSITY_ELEMENT
      Serial.print(F("Light intensity end. New value: "));
      Serial.print(newLightValue);
      Serial.println(F(" lux"));
      #endif

      //Reset the state machine
      StateMachine = BHI_1750FVI_LIGHT_INTENSITY_STATE_WAIT;
    }
    else if((millis() - LastSampleTime) > BHI_1750FVI_LIGHT_INTENSITY_MAX_SAMPLE_TIME){
      //Sample of data was not done in the desired sample time. Restart the state machine.
      StateMachine = BHI_1750FVI_LIGHT_INTENSITY_STATE_START_CONVERSION;
    }
  }
}

#endif //BHI_1750FVI_LIGHT_INTENSITY_ENABLED