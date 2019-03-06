

#include "../AllYouNeedIsStartHere/tcp_ip_settings.h"
#include <WString.h>
#include <Ethernet2.h>

class TCP_SERVER
{
    public:

    bool8 initiate(void);

    String* loop(void);

    void send_data(String &Data);

    private:

    String ReceivedData;

    // Initialize the Ethernet client library
    EthernetClient client;

};