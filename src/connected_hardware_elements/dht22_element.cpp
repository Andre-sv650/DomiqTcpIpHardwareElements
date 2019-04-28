

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
  //Set the temperature and humditiy to invalid values.
  Temperature = -500;
  Humidity = -500;
  Dht22NotAvailableDebugMessageSet = 0u;

  // Data wire is plugged on the Arduino
  // Connect a 4.7K or 10K resistor between VCC and the data pin (strong pullup) Setup a DHT22 instance
  MyDht22.begin(Pin, DHT22);

  //Set the last read time to 0. The data should be read direct.
  LastReadTime = 0u;
}

void DHT22_ELEMENT::initiate(const String &TemperatureVarNameInDomiq, Uint8 Pin, const String &HumidityVarNameInDomiq)
{
  this->initiate(TemperatureVarNameInDomiq, Pin);

  this->HumidityVarName = HumidityVarNameInDomiq;
}

void DHT22_ELEMENT::background_routine(void)
{
  Uint32 currentTime = millis();

  if ((currentTime - LastReadTime) > DHT22_ELEMENT_READ_DATA_CYCLE)
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
      if (Dht22NotAvailableDebugMessageSet < 200)
      {
        //Do not set the new data.
        humidity = Humidity;
        temperature = Temperature;

        Dht22NotAvailableDebugMessageSet++;
      }
      else if (Dht22NotAvailableDebugMessageSet >= 200)
      {
        temperature = -Dht22NotAvailableDebugMessageSet;
        humidity = -Dht22NotAvailableDebugMessageSet;

        Dht22NotAvailableDebugMessageSet++;
      }
    }
    else
    {
      Dht22NotAvailableDebugMessageSet = 0;
    }
    //Check if data was changed.
    if (Temperature != temperature)
    {
      String temperatur = String(Temperature);

      //Set the new temperature to the base element.
      set_new_data_sampled(temperatur);

      this->NewDataSampled = TRUE;
    }

    if ((Humidity != humidity))
    {
      this->NewDataSampled = TRUE;
    }

    Humidity = humidity;
    Temperature = temperature;

    //Save the time.
    LastReadTime = currentTime;
  }
}

String DHT22_ELEMENT::get_sampled_data(void)
{
  String newSampledData;

  if (this->NewDataSampled == TRUE)
  {
    String temperatur = CONNECTED_ELEMENT_BASE::get_sampled_data();
    String humidity = CONNECTED_ELEMENT_BASE::generate_domiq_string(HumidityVarName, Humidity);

    CONNECTED_ELEMENT_BASE::debug_message_new_sampled_data(HumidityVarName, String(Humidity));
    newSampledData = temperatur + humidity;
  }

  return newSampledData;
}

#endif //DHT22_ELEMENT_ENABLED
