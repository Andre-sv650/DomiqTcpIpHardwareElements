

#include "datatypes/cpu_datatypes.h"
#include "tcp_server.h"
#include <SPI.h>
#include <Ethernet2.h>
#include "debug/debug_data.h"

bool8 TCP_SERVER::initiate(void)
{
  bool8 connectionEstablished = FALSE;
  // Set a static IP address to use if the DHCP fails to assign
  IPAddress ip(OWN_IP);
  byte mac[] = OWN_MAC_SETTING;
  char domiqBaseIp[] = DOMIQ_BASE_IP;

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
  delay(1000);
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

    // Now sleep until a reset
    while (true)
      ;
  }

  return &ReceivedData;
}