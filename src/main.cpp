#include "AllYouNeedIsStartHere/project_defines.h"
#include <SPI.h>
#include "AllYouNeedIsStartHere/sensor_elements_initiate.h"
#include "AllYouNeedIsStartHere/sensor_elements_keller_initiate.h"
#include "AllYouNeedIsStartHere/sensor_elements_uno_initiate.h"
#include "tcp_server/tcp_server_ethernet2.h"
#include "tcp_server/tcp_server_esp8266.h"
#include "connected_hardware_elements/Base/connected_element_array.h"
#include "connected_hardware_elements/RcSwitch433Mhz/rc_switch_433_mhz_base_instance.h"
#include "HelperFunctions/eeprom_initialize.h"
 

#ifdef NODEMCU
SENSOR_ELEMENTS_KELLER_INITIATE sensorElements;

// Initialize the Ethernet client library
TCP_SERVER_ESP8266 server;

#elif UNO

SENSOR_ELEMENTS_UNO_INITIATE sensorElements;

TCP_SERVER_ETHERNET2 server;

#else
SENSOR_ELEMENTS_INITIATE sensorElements;

// Initialize the Ethernet client library
TCP_SERVER_ETHERNET2 server;
#endif

 
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(SERIAL_COMMUNICATION_SPEED);

  #ifdef NODEMCU

  //Node mcu does not have an EEPROM. EEPROM is not supported until now.
  #else

  //Check if the EEPROM has to be initialized.
  EEPROM_INITIALIZE::initialize(EEPROM_KEY1, EEPROM_KEY2);

  #endif

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

  //Check if the background routine for the RC switch should be checked.
  #ifdef RC_SWITCH_433MHZ_ENABLED

  RC_SWITCH_433MHZ_BASE_INSTANCE::background_routine();

  #endif

  String sendData = CONNECTED_ELEMENT_ARRAY::get_new_data();

  server.send_data(sendData);
}


