#ifdef NODEMCU
#include <ESP8266WiFi.h>
#include "tcp_server.h"

#ifndef TCP_SERVER_ESP8266_H
#define TCP_SERVER_ESP8266_H

class TCP_SERVER_ESP8266 : public TCP_SERVER
{
    public:

    virtual bool8 initiate(void);

    protected:
    
    virtual bool8 client_connect(const char DomiqBaseIp[], Uint32 Port);

    virtual void client_println(String &Data);

    virtual int client_available(void);

    virtual int client_read(Uint8 buf[], size_t size);

    virtual int client_connected(void);

    virtual void client_stop(void);


    private:

    WiFiClient wifiClient;

};

#endif //TCP_SERVER_ESP8266_H

#endif