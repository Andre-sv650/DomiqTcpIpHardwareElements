
#include "stm_vl53l0x_element.h"
#ifdef STM_VL53L0X_ELEMENT_ENABLED

//Default constructor.
STM_VL53L0X_ELEMENT::STM_VL53L0X_ELEMENT()
{
}

/*
  /*
 * STM time to flight sensor for ranges. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * If an XSHUT PIN is available. connect it to an GPIO Input with a pull up resistor.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
void STM_VL53L0X_ELEMENT::initiate(const String &VarNameInDomiq)
{
  Uint8 retryCnt;
  // Initialize I2C bus
  Wire.begin();

  while(!lox.begin() && retryCnt < 10){
    Serial.println("Failed to boot VL53L0X");
    delay(1000);
    retryCnt++;
  }

  CONNECTED_ELEMENT_BASE::initiate(VarNameInDomiq);
}

//Background routine for the STM VL53 element intensity.
void STM_VL53L0X_ELEMENT::background_routine()
{
  VL53L0X_RangingMeasurementData_t measure;
  VL53L0X_Error readError = lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
      // Read light without wait
      Uint16 newRangeInmm = Filter.filter_value(measure.RangeMilliMeter, STM_RANGE_MIN_DIFFERENCE, STM_RANGE_VALUE_DIFFERENT);
      String newValue = String(newRangeInmm);

      //Set the sampled data.
      CONNECTED_ELEMENT_BASE::set_new_data_sampled(newValue);
  } else {
    //Serial.println(" out of range ");
  }
}

#endif //BHI_1750FVI_LIGHT_INTENSITY_ENABLED