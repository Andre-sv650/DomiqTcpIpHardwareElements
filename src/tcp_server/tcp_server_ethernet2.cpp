#if defined(ETHERNET_SHIELD)
#include "datatypes/cpu_datatypes.h"
#include "tcp_server_ethernet2.h"
#include <SPI.h>
#include "debug/debug_data.h"



bool8 TCP_SERVER_ETHERNET2::initiate(void)
{  
  // Set a static IP address to use if the DHCP fails to assign
  IPAddress ip(OWN_IP);
  byte mac[] = OWN_MAC_SETTING;

  TCP_SERVER::initiate();

  // Start the Ethernet connection:
  if (Ethernet.begin(mac) == 0){
    DEBUG_DATA::tcp_server_failed_to_connect();

    // Can't get an IP, so use another one
    Ethernet.begin(mac, ip);
  }
  else{
    IPAddress localIp = Ethernet.localIP();

    DEBUG_DATA::tcp_server_connected_to_network(localIp);
  }

  // Give the Ethernet shield some time to initialize.
  delay(250);

  //Connect to domiq base.
  return connect_to_domiq();
}

//--------------------------------protected functions ------------------------------------

bool8 TCP_SERVER_ETHERNET2::client_connect(const char DomiqBaseIp[], Uint32 Port)
{
    return client.connect(DomiqBaseIp, Port);
}


void TCP_SERVER_ETHERNET2::client_println(String &Data)
{
  client.println(Data);
}


int TCP_SERVER_ETHERNET2::client_available(void)
{
  return client.available();
}

int TCP_SERVER_ETHERNET2::client_read(Uint8 buf[], size_t size)
{
  return client.read(buf, size);
}

int TCP_SERVER_ETHERNET2::client_connected(void)
{
  return client.connected();
}

void TCP_SERVER_ETHERNET2::client_stop(void)
{
  client.stop();
}

#endif //#ifdef ETHERNET2_HARDWARE