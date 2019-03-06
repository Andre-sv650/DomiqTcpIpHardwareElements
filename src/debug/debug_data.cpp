
#include "debug_data.h"
#include <Arduino.h>

namespace DEBUG_DATA
{
  void tcp_server_failed_to_connect(void)
  {
    #ifdef DEBUG_DATA_TCP_SERVER
    
    Serial.println("Failed to configure Ethernet using DHCP");

    #endif
  }

  void tcp_server_connected_to_network(String IpAddress)
  {
    #ifdef DEBUG_DATA_TCP_SERVER
    
    Serial.println("Own IP address is: " + IpAddress);

    #endif
  }
  
  
  void tcp_server_print_command_received(Uint8 Length, const String &DataValue)
  {
    #ifdef DEBUG_DATA_TCP_SERVER
    
    String serialPrintfData = "New data from domiq received. Length: " + String(Length) + ". Data is: " + DataValue;
    Serial.println(serialPrintfData);

    #endif
  }


  void tcp_server_print_send_new_data(String &Data)
  {
    #ifdef DEBUG_DATA_TCP_SERVER

    String printLine = "Sending data to domiq done, data was: " + Data;
    Serial.println(printLine); 

    #endif
  }


  void connected_element_array_item_added(bool8 Success)
  {
    #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY

    if(Success == TRUE){
      Serial.println("A new element was registered");
    }
    else{
      Serial.println("Could not register new element");
    }

    #endif
  }


  void connected_element_array_item_found_setting_data(String &ItemName, String &Value)
  {
    #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY
    Serial.println("Element found, setting data for: " + ItemName + ". With Value: " + Value);

    #endif
  }


  void connected_element_array_found_new_data(String &VariableName, String &Value)
  {
    #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY
    Serial.println("New data was found for variale: " + VariableName + ". With value " + Value);

    #endif
  }



  void relais_element_set_data_called(String NewData)
  {
    #ifdef DEBUG_RELAIS_SET

    String serialPrintData = "New data from domiq for Relay was received. Data: " + NewData;
    Serial.println(serialPrintData);

    #endif
  }

  void relais_element_set_data_to_pin(char Pin)
  {
    #ifdef DEBUG_RELAIS_SET
    
    String serialPrintData = "Setting Pin: " + Pin;
    Serial.println(serialPrintData);

    #endif
  }

  void relais_element_get_data_called(String &ReturnedValue)
  {
    #ifdef DEBUG_RELAIS_SET
    
    String serialPrintData = "Get data was called, returned the follwing data: " + ReturnedValue;
    Serial.println(serialPrintData);

    #endif
  }

  void temp_sensor_one_wire_new_data_sampled(String &NewData)
  {
    String tempSensorData = "New temp sensor data sampled: " + NewData;
    Serial.println(tempSensorData);
  }


  void generic_send_debug_message(String &Message)
  {
    Serial.println(Message);
  }
}

