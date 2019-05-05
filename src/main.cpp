#include "AllYouNeedIsStartHere/project_defines.h"
#include <SPI.h>
#include "AllYouNeedIsStartHere/sensor_elements_initiate.h"
#include "AllYouNeedIsStartHere/sensor_elements_keller_initiate.h"
#include "tcp_server/tcp_server.h"
#include "connected_hardware_elements/Base/connected_element_array.h"
#include "HelperFunctions/eeprom_initialize.h"
 

#ifdef KELLER
SENSOR_ELEMENTS_KELLER_INITIATE sensorElements;
#else
SENSOR_ELEMENTS_INITIATE sensorElements;
#endif

// Initialize the Ethernet client library
TCP_SERVER server;
 
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  //Delay of 500ms to ensure that the connected PC is ready for serial communication.
  delay(500)

  //Check if the EEPROM has to be initialized.
  EEPROM_INITIALIZE::initialize(EEPROM_KEY1, EEPROM_KEY2);

  //Initialize the sensor elements.
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


