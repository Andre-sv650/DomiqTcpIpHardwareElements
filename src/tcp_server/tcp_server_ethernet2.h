#if defined(ETHERNET_SHIELD)

#include "../external_library_ethernet/stoffregen_ethernet/Ethernet.h"
#include "tcp_server.h"
#include "datatypes/cpu_datatypes.h"
#include <WString.h>

#ifndef TCP_SERVER_ETHERNET2_H
#define TCP_SERVER_ETHERNET2_H

class TCP_SERVER_ETHERNET2 : public TCP_SERVER
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

    // Initialize the Ethernet client library
    EthernetClient client;

    Uint32 LastReceivedDataAtTime;
};

#endif //TCP_SERVER_ETHERNET2_H

#endif //ETHERNET_SHIELD