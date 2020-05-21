/********************************
 * Use the shield as following. 
 * (https://arduinobasics.blogspot.com/2018/09/getting-started-with-keyes-esp-13-wifi.html)
 * 1. Connect the Uart RX pin to the TX pin of the arduino
 * 2. Connnect the UART TX pin to the RX pin of the arduino.
 * 3. Connect the 5V and the ground to the aruino.
 * 4. Both switches has to be set to on.
 * 
 * Set the baud rate to 9600 (only needed if software UART is used.)
 * via login to the device wlan or via a command.
 * Via a command, connect the debug pins of the board to the arduino.
 */


#ifdef USE_TCP_SERVER_ESP13_SHIELD
#include "tcp_server/tcp_server_esp13_shield.h"
#include "WifiEsp.h"

//#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#define RX_PIN_FROM_ESP13_BOARD 2
#define TX_PIN_FROM_ESP13_BOARD 3
#define TCP_SERVER_ESP13_SHIELD_COM_BAUDRATE 9600


SoftwareSerial SoftwareSerial0(RX_PIN_FROM_ESP13_BOARD, TX_PIN_FROM_ESP13_BOARD); // RX, TX
//#endif


bool8 TCP_SERVER_ESP13_SHIELD::initiate(void)
{
  int status = WL_IDLE_STATUS;     // the Wifi radio's status

  TCP_SERVER::initiate();

  //Reset the wifi shield.
  //pinMode(4, OUTPUT);
  //digitalWrite(4, LOW);

  //delay(1000);

  //Start the ESP module.
  //digitalWrite(4, HIGH);

  Serial.print("ESP13 Shield RX on Pin: ");
  Serial.println(RX_PIN_FROM_ESP13_BOARD);
  Serial.print("ESP13 Shield TX on Pin: ");
  Serial.println(TX_PIN_FROM_ESP13_BOARD);

  // initialize serial for ESP module
  SoftwareSerial0.begin(TCP_SERVER_ESP13_SHIELD_COM_BAUDRATE);
  // initialize ESP module
  WiFi.init(&SoftwareSerial0);

  // check for the presence of the shield
  if(WiFi.status() == WL_NO_SHIELD){
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  Serial.print(F("Connecting to network: "));
  Serial.println(WIFI_NETWORK_SSID);

  while (status != WL_CONNECTED) {
    delay(500);
    Serial.println(F("Connecting to WiFi.."));

    status = WiFi.begin(WIFI_NETWORK_SSID, WIFI_NETWORK_PASSWORD);
  }
 
  Serial.println(F("Connected to the WiFi network")); 
  Serial.print(F("Your IP address is: "));
  Serial.println(WiFi.localIP());

  print_wifi_status();

  return TRUE;
}


//--------------------------------protected functions ------------------------------------

bool8 TCP_SERVER_ESP13_SHIELD::client_connect(const char DomiqBaseIp[], Uint32 Port)
{
  return wifiClient.connect(DomiqBaseIp, Port);
}


void TCP_SERVER_ESP13_SHIELD::client_println(String &Data)
{
  wifiClient.println(Data);
}


int TCP_SERVER_ESP13_SHIELD::client_available(void)
{
  return wifiClient.available();
}


int TCP_SERVER_ESP13_SHIELD::client_read(Uint8 buf[], size_t size)
{
  return wifiClient.read(buf, size);
}

int TCP_SERVER_ESP13_SHIELD::client_connected(void)
{
  return wifiClient.connected();
}

void TCP_SERVER_ESP13_SHIELD::client_stop(void)
{
  //No stop required. Just initiate the domiq base connection new.
  //wifiClient.stop();
}


void TCP_SERVER_ESP13_SHIELD::print_wifi_status(void)
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


#endif //TCP_SERVER_ESP13_SHIELD
