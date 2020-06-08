//Global settings

//This is the buffer size in byte for reading data from the ethernet shild (or node mcu shield)
//Decrease it, if you have not enough free ram any more.
#define TCP_SERVER_CLIENT_READ_MULTIBYTE_BUFFER_SIZE 40


#ifdef NODEMCU

//SSID of your network
#define WIFI_NETWORK_SSID "YourNetworkName"

//password of your WPA Network
#define WIFI_NETWORK_PASSWORD  "YourNetworkPassword"

// If your Arduino has a MAC address, use this instead
#define OWN_MAC_SETTING { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }

#elif UNO

//SSID of your network
#define WIFI_NETWORK_SSID "YourNetworkName"

//password of your WPA Network
#define WIFI_NETWORK_PASSWORD  "YourNetworkPassword"

// Set a static IP address to use if the DHCP fails to assign. Not used for ESP8266 for wifi connection.
#define OWN_IP {192, 168, 2, 180}

// If your Arduino has a MAC address, use this instead
#define OWN_MAC_SETTING { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF }


#else

//SSID of your network
#define WIFI_NETWORK_SSID "YourNetworkName"

//password of your WPA Network
#define WIFI_NETWORK_PASSWORD  "YourNetworkPassword"

// Set a static IP address to use if the DHCP fails to assign. Not used for ESP8266 for wifi connection.
#define OWN_IP {192, 168, 2, 171}

// If your Arduino has a MAC address, use this instead
#define OWN_MAC_SETTING { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }

#endif


#define DOMIQ_BASE_IP "192.168.2.155"   // IP of domiq base


//The time out. If not data from domiq is received in this time, the connection is restarted.
//This is needed, because if the connection fails, domiq will disconnect the client and nothing will be send and 
//received an more. The unit is milli seconds.
#define TCP_IP_SETTINGS_TIMEOUT_IN_MS 50000u

