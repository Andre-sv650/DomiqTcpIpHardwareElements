
#include <SPI.h>
#include "AllYouNeedIsStartHere/sensor_elements_initiate.h"
#include "tcp_server/tcp_server.h"
#include "connected_hardware_elements/connected_element_array.h"
 
// Initialize the Ethernet client library
SENSOR_ELEMENTS_INITIATE sensorElements;
TCP_SERVER server;
 
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);

  sensorElements.initiate();

  //Try to establish connection to base till it is ready.
  while(server.initiate() == FALSE);
}
 
void loop()
{
  String ReceivedData = *server.loop();

  CONNECTED_ELEMENT_ARRAY::set_new_data_from_domiq(ReceivedData);

  CONNECTED_ELEMENT_ARRAY::background_routine();

  String sendData = CONNECTED_ELEMENT_ARRAY::get_new_data();

  server.send_data(sendData);
}


