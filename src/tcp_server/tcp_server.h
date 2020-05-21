#include "../AllYouNeedIsStartHere/tcp_ip_settings.h"
#include "datatypes/cpu_datatypes.h"
#include <WString.h>

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

class TCP_SERVER
{
    public:

    virtual bool8 initiate(void);

    virtual bool8 connect_to_domiq(void);

    void loop();

    String ReceivedData;

    String TempReceiveBuffer;

    void send_data(String &Data);

    private:

    Uint32 LastReceivedDataAtTime;

    Uint8 ReconnectCounter;

    protected:

    virtual bool8 client_connect(const char DomiqBaseIp[], Uint32 Port) = 0;

    virtual void client_println(String &Data) = 0;

    virtual int client_available(void) = 0;

    virtual int client_read(Uint8 buf[], size_t size) = 0;

    virtual int client_connected(void) = 0;

    virtual void client_stop(void) = 0;

    private:

    //Initialize one buffer.
    Uint8 buffer[TCP_SERVER_CLIENT_READ_MULTIBYTE_BUFFER_SIZE];

    bool8 client_read_multibyte_data(void);

    bool8 copy_received_char_array_to_string(Uint8 Size);
};

#endif //TCP_SERVER_H