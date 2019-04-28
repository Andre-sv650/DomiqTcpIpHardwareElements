


// If your Arduino has a MAC address, use this instead
#define OWN_MAC_SETTING { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }
#define DOMIQ_BASE_IP "192.168.2.155"   // IP of domiq base
 
// Set a static IP address to use if the DHCP fails to assign
#define OWN_IP {192, 168, 2, 170}

//The time out. If not data from domiq is received in this time, the connection is restarted.
//This is needed, because if the connection fails, domiq will disconnect the client and nothing will be send and 
//received an more. The unit is milli seconds.
#define TCP_IP_SETTINGS_TIMEOUT_IN_MS 50000u