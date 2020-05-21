#ifdef USE_TCP_SERVER_ESP13_SHIELD
#include "../AllYouNeedIsStartHere/tcp_ip_settings.h"
#include "WiFiEspClient.h"
#include "tcp_server.h"

#ifndef TCP_SERVER_ESP13SHIELD_H
#define TCP_SERVER_ESP13SHIELD_H

class TCP_SERVER_ESP13_SHIELD : public TCP_SERVER
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

    WiFiEspClient wifiClient;

    void print_wifi_status(void);

};

#endif //TCP_SERVER_ESP13SHIELD_H

#endif //TCP_SERVER_ESP13_SHIELD