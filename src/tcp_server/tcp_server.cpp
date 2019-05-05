#include "datatypes/cpu_datatypes.h"
#include "tcp_server.h"
#include <SPI.h>
#include "debug/debug_data.h"

bool8 TCP_SERVER::initiate(void)
{
  // Set a static IP address to use if the DHCP fails to assign
  IPAddress ip(OWN_IP);
  byte mac[] = OWN_MAC_SETTING;

  // Start the Ethernet connection:
  if (Ethernet.begin(mac) == 0)
  {
    DEBUG_DATA::tcp_server_failed_to_connect();

    // Can't get an IP, so use another one
    Ethernet.begin(mac, ip);
  }
  else
  {
    IPAddress localIp = Ethernet.localIP();

    DEBUG_DATA::tcp_server_connected_to_network(String(localIp));
  }
  // Give the Ethernet shield some time to initialize:
  delay(500);

  //Connect to domiq base.
  return connect_to_domiq();
}


bool8 TCP_SERVER::connect_to_domiq(void)
{
  const char domiqBaseIp[] = DOMIQ_BASE_IP;
  bool8 connectionEstablished = FALSE;

  Serial.println("Connecting to Domiq base with IP: " + String(domiqBaseIp));

  // Are we connected?
  if (client.connect(domiqBaseIp, 4224))
  {
    Serial.println("Domiq connection established.");
    connectionEstablished = TRUE;
  }
  else
  {
    // Warn if the connection wasn't made
    Serial.println("Connection failed, trying again.");
  }

  //Save the time.
  LastReceivedDataAtTime = millis();

  return connectionEstablished;
}


void TCP_SERVER::send_data(String &Data)
{
  if (Data.length() > 0)
  {
    // Make a HTTP request:
    client.println(Data);

    DEBUG_DATA::tcp_server_print_send_new_data(Data);
  }
}


String* TCP_SERVER::loop()
{
  Uint16 i = 0;
  bool8 dataReceived = FALSE;
  ReceivedData = "";
  while (client.available())
  {
    //Read each byte on its own. Dont use the funtion read with a pointer to an array. This method will reset the device.
    //Dont know where the problem is.
    int data = client.read();
    if(data > -1){
      ReceivedData += (char)data;
      i++;
    }

    dataReceived = TRUE;
  }

  if(dataReceived == TRUE){
    //Save the time.
    LastReceivedDataAtTime = millis();
  }
  else{
    //No data received. Something is wrong.
    Uint32 currentTime = millis();
    if((currentTime - LastReceivedDataAtTime) > TCP_IP_SETTINGS_TIMEOUT_IN_MS){
      Serial.println("Reastablishing connection");

      client.stop();
      connect_to_domiq();
    }

  }
  // Check for incoming bytes
  if (i > 0)
  {
    DEBUG_DATA::tcp_server_print_command_received(i, ReceivedData);
  }

  // If the server disconnected, then stop the client:
  if (!client.connected())
  {
    Serial.println("Disconnecting.");
    client.stop();

    connect_to_domiq();
  }

  return &ReceivedData;
}