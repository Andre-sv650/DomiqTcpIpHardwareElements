

#include "dht22_element.h"
#ifdef DHT22_ELEMENT_ENABLED

// Depends on the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// See guide for details on sensor wiring and usage:
// https://learn.adafruit.com/dht/overview

#include "../debug/debug_data.h"

void DHT22_ELEMENT::initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin)
{
  CONNECTED_ELEMENT_BASE::initiate(Pin, TemperatureVarNameInDomiq);
  
  //Set the temperature and humditiy to invalid values.
  initiate();
}


void DHT22_ELEMENT::initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin, const String &HumidityVarNameInDomiq)
{
  CONNECTED_ELEMENT_BASE::initiate(Pin, TemperatureVarNameInDomiq);

  this->HumidityVarName = HumidityVarNameInDomiq;
  
  initiate();

  //Call the background routine once at startup.
  background_routine();
}

void DHT22_ELEMENT::initiate(void)
{
    //Set the temperature and humditiy to invalid values.
  Temperature = -500;
  Humidity = -500;
  Dht22NotAvailableDebugMessageSet = 0u;

    // Data wire is plugged on the Arduino
  // Connect a 4.7K or 10K resistor between VCC and the data pin (strong pullup) Setup a DHT22 instance
  MyDht22.begin(Pin, DHT22);
}


void DHT22_ELEMENT::background_routine(void)
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = MyDht22.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = MyDht22.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = 0.0f; // MyDht22.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature) || isnan(f))
  {
    if(Dht22NotAvailableDebugMessageSet < 200){
      Dht22NotAvailableDebugMessageSet++;
    }

    if(Dht22NotAvailableDebugMessageSet == 200){
      //MODBUS_DEBUG::print_dht22_not_available(Pin);
      Temperature = -500;
      Humidity = -500;

      Dht22NotAvailableDebugMessageSet = 201;
    }
  }
  else{
    if(Dht22NotAvailableDebugMessageSet > 200){
      
      //MODBUS_DEBUG::print_dht22_now_available(Pin);
    }

    Dht22NotAvailableDebugMessageSet = 0;

    //Data valid. Set the data.
    //Check if data was changed.
    if(Humidity != humidity || Temperature != temperature){
      this->NewDataSampled = TRUE;
    }
    
    Humidity = humidity;
    Temperature = temperature;
  }
}


String DHT22_ELEMENT::get_sampled_data(void)
{
 String newSampledData;

 if(this->NewDataSampled == TRUE){
 
  String temperatur = CONNECTED_ELEMENT_BASE::generate_domiq_string(Temperature);
  String humidity = CONNECTED_ELEMENT_BASE::generate_domiq_string(HumidityVarName, Humidity);

  newSampledData = temperatur + humidity;
 }

 return newSampledData;
}

#endif //DHT22_ELEMENT_ENABLED
