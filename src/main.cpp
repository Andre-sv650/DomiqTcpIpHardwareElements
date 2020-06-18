#include "AllYouNeedIsStartHere/project_defines.h"
#include <SPI.h>
#include "AllYouNeedIsStartHere/sensor_elements_initiate.h"
#include "AllYouNeedIsStartHere/sensor_elements_keller_initiate.h"
#include "AllYouNeedIsStartHere/sensor_elements_uno_initiate.h"
#include "tcp_server/tcp_server_ethernet2.h"
#include "tcp_server/tcp_server_esp8266.h"
#include "tcp_server/tcp_server_esp13_shield.h"
#include "connected_hardware_elements/Base/connected_element_array.h"
#include "connected_hardware_elements/RcSwitch433Mhz/rc_switch_433_mhz_base_instance.h"
#include "HelperFunctions/eeprom_initialize.h"
#include "watchdog/watchdog.h"
 

#ifdef NODEMCU
SENSOR_ELEMENTS_KELLER_INITIATE sensorElements;

// Initialize the Ethernet client library
TCP_SERVER_ESP8266 server;

#elif UNO

SENSOR_ELEMENTS_UNO_INITIATE sensorElements;

#else

SENSOR_ELEMENTS_INITIATE sensorElements;

#endif

#ifdef ETHERNET_SHIELD
// Initialize the Ethernet client library
TCP_SERVER_ETHERNET2 server;

#elif USE_TCP_SERVER_ESP13_SHIELD

TCP_SERVER_ESP13_SHIELD server;

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

  Serial.println(F("Software started"));

  //Initialize the sensor elements.
  sensorElements.initiate();

  //Initiate the server.
  server.initiate();

  //Try to establish connection to base till it is ready.
  while(server.connect_to_domiq() == FALSE){
    //No connection available try again.
    Serial.println(F("Connection failed, retry"));

    //1000ms delay for the reconnection.
    delay(1000);
  }

  //Start the software watchdog.
  watchdog_enable();
}
 
void loop()
{
  String sendData;

  //Check for incoming messages from Domiq base.
  bool8 connectionOk = server.loop();

  if(connectionOk == FALSE){
    //The connection was reconnected. Report the last sampled data again.
    CONNECTED_ELEMENT_ARRAY::report_sampled_data_to_domiq_after_reconnect();
  }

  //Set the new data that was received.
  CONNECTED_ELEMENT_ARRAY::set_new_data_from_domiq(server.ReceivedData);

  CONNECTED_ELEMENT_ARRAY::background_routine();

  //Check if the background routine for the RC switch should be checked.
  #ifdef RC_SWITCH_433MHZ_ENABLED

  RC_SWITCH_433MHZ_BASE_INSTANCE::background_routine();

  #endif

  CONNECTED_ELEMENT_ARRAY::get_new_data(sendData);

  server.send_data(sendData);

  //Reset the software watchdog.
  watchdog_reset_time();
}


