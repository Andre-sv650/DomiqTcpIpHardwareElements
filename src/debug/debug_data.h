
#include "../AllYouNeedIsStartHere/project_defines.h"
#include "../AllYouNeedIsStartHere/debug_defines.h"
#include "../datatypes/cpu_datatypes.h"
#include <WString.h>

namespace DEBUG_DATA
{
  void tcp_server_failed_to_connect(void);

  void tcp_server_connected_to_network(String IpAddress);
  
  void tcp_server_print_command_received(Uint8 Length, const String &DataValue);


  void tcp_server_print_send_new_data(String &Data);



  void connected_element_array_item_added(String ElementName);

  void connected_element_array_item_found_setting_data(String &ItemName, String &Value);

  void connected_element_array_found_new_data(String &VariableName, String &Value);



  void relais_element_set_data_called(String NewData);

  void relais_element_set_data_to_pin(char Pin);

  void relais_element_get_data_called(String &ReturnedValue);


  void temp_sensor_one_wire_new_data_sampled(String &NewData);

  void generic_send_debug_message(String &Message);
};
