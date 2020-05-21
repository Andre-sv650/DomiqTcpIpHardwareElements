
#include "debug_data.h"
#include <Arduino.h>

namespace DEBUG_DATA
{
  void tcp_server_failed_to_connect(void)
  {
    #ifdef DEBUG_DATA_TCP_SERVER
    
    Serial.println(F("Failed: DHCP"));

    #endif
  }

  void tcp_server_connected_to_network(IPAddress IpAddress)
  {
    #ifdef DEBUG_DATA_TCP_SERVER
        
    Serial.print(F("Own IP address: "));
    Serial.println(IpAddress);

    #endif
  }
  
  
  void tcp_server_print_command_received(const String &DataValue)
  {
    #ifdef DEBUG_DATA_TCP_SERVER
    
    Serial.print(F("Data received. Length: "));
    Serial.print(String(DataValue.length()));
    Serial.print(F(". Data: "));
    Serial.print(DataValue);

    #endif
  }


  void tcp_server_print_send_new_data(String &Data)
  {
    #ifdef DEBUG_DATA_TCP_SERVER

    Serial.print(F("Send data done, data: "));
    Serial.print(Data); 

    #endif
  }


  void connected_element_array_item_added(String &ElementName)
  {
    Serial.print(F("Element registered: "));
    Serial.println(ElementName);
  }


  void connected_element_array_item_found_setting_data(String &ItemName, String &Value)
  {
    #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY
    Serial.print(F("Element found, set data: "));
    Serial.println(ItemName + ". Value: " + Value);

    #endif
  }


  void connected_element_array_found_new_data(String &Value)
  {
    #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY
    Serial.print(F("New data for variable: "));
    Serial.println(Value);

    #endif
  }



  void relais_element_set_data_called(String &NewData)
  {
    #ifdef DEBUG_RELAIS_SET

    Serial.print(F("Data for Relay received: "));
    Serial.println(NewData);

    #endif
  }

  void relais_element_set_data_to_pin(Uint8 Pin, Uint8 Value)
  {
    #ifdef DEBUG_RELAIS_SET
    Serial.print(F("Setting Pin: "));
    Serial.print(Pin);
    Serial.print(F(". To value: "));
    Serial.println(Value);

    #endif
  }

  void relais_element_get_data_called(String &ReturnedValue)
  {
    #ifdef DEBUG_RELAIS_SET
    Serial.print(F("Get data called, returned data: "));
    Serial.println(ReturnedValue);

    #endif
  }

  void temp_sensor_one_wire_new_data_sampled(String &NewData)
  {
    Serial.print(F("New temp sensor one wire sampled: "));
    Serial.println(NewData);
  }
}

