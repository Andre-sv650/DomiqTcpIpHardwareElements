
#include "../AllYouNeedIsStartHere/project_defines.h"
#include "../AllYouNeedIsStartHere/debug_defines.h"
#include "../datatypes/cpu_datatypes.h"
#include "IPAddress.h"
#include <WString.h>

namespace DEBUG_DATA
{
  void tcp_server_failed_to_connect(void);

  void tcp_server_connected_to_network(IPAddress IpAddress);
  
  void tcp_server_print_command_received(const String &DataValue);


  void tcp_server_print_send_new_data(String &Data);



  void connected_element_array_item_added(String &ElementName);

  void connected_element_array_item_found_setting_data(String &ItemName, String &Value);

  void connected_element_array_found_new_data(String &Value);



  void relais_element_set_data_called(String &NewData);

  void relais_element_set_data_to_pin(Uint8 Pin, Uint8 Value);

  void relais_element_get_data_called(String &ReturnedValue);


  void temp_sensor_one_wire_new_data_sampled(String &NewData);
};
