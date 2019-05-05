
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
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
void BHI_1750FVI_LIGHT_INTENSITY::initiate(const String &VarNameInDomiq)
{
  // Initialize I2C bus
  Wire.begin();

  // Initialize sensor in continues mode, high 0.5 lx resolution
  Sensor.begin(ModeContinuous, ResolutionHigh);

  // Start conversion
  Sensor.startConversion();

  CONNECTED_ELEMENT_BASE::initiate(VarNameInDomiq);
}

//Background routine for the light intensity.
void BHI_1750FVI_LIGHT_INTENSITY::background_routine()
{
  // Read light without wait
  Uint16 light = Sensor.read();
  Uint16 newLight = Filter.filter_value(light, LIGHT_VALUE_MIN_DIFFERENCE, LIGHT_VALUE_DIFFERENT);
  //Calculate the new value.
  String newLightValue = String(newLight / 2) + "." + String(newLight % 10);

  //Set the sampled data.
  CONNECTED_ELEMENT_BASE::set_new_data_sampled(newLightValue);

  //Start a new conversion.
  Sensor.startConversion();
}

#endif //BHI_1750FVI_LIGHT_INTENSITY_ENABLED