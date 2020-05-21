
#ifdef NODEMCU
#include "tcp_server_esp8266.h"


bool8 TCP_SERVER_ESP8266::initiate(void)
{
  TCP_SERVER::initiate();
  
  WiFi.begin(WIFI_NETWORK_SSID, WIFI_NETWORK_PASSWORD);
  Serial.print(F("Connecting to network: "));
  Serial.println(WIFI_NETWORK_SSID);
    

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(F("Connecting to WiFi.."));
  }
 
  Serial.println(F("Connected to the WiFi network")); 
  Serial.print(F("Your IP address is: "));
  Serial.println(WiFi.localIP());

  return TRUE;
}


//--------------------------------protected functions ------------------------------------

bool8 TCP_SERVER_ESP8266::client_connect(const char DomiqBaseIp[], Uint32 Port)
{
    return wifiClient.connect(DomiqBaseIp, Port);
}


void TCP_SERVER_ESP8266::client_println(String &Data)
{
  wifiClient.println(Data);
}


int TCP_SERVER_ESP8266::client_available(void)
{
  return wifiClient.available();
}


int TCP_SERVER_ESP8266::client_read(Uint8 buf[], size_t size)
{
  return wifiClient.read(buf, size);
}

int TCP_SERVER_ESP8266::client_connected(void)
{
  return wifiClient.connected();
}

void TCP_SERVER_ESP8266::client_stop(void)
{
  wifiClient.stop();
}

#endif //NODEMCU










