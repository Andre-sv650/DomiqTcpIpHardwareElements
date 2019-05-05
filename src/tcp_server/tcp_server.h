#include <Ethernet.h>
#include "../AllYouNeedIsStartHere/tcp_ip_settings.h"
#include <WString.h>

class TCP_SERVER
{
    public:

    bool8 initiate(void);

    bool8 connect_to_domiq(void);

    String* loop(void);

    void send_data(String &Data);

    private:

    String ReceivedData;

    // Initialize the Ethernet client library
    EthernetClient client;

    Uint32 LastReceivedDataAtTime;

};