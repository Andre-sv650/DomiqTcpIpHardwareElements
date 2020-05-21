#include "datatypes/cpu_datatypes.h"
#include "tcp_server.h"
#include <SPI.h>
#include "debug/debug_data.h"


bool8 TCP_SERVER::initiate(void)
{
  //Reset the counter.
  ReconnectCounter = 0u;

  LastReceivedDataAtTime = millis();

  ReceivedData = "";

  TempReceiveBuffer = "";
}

bool8 TCP_SERVER::connect_to_domiq(void)
{
  const char domiqBaseIp[] = DOMIQ_BASE_IP;
  bool8 connectionEstablished = FALSE;

  Serial.print(F("Connecting to Domiq base with IP: "));
  Serial.println(String(domiqBaseIp));

  // Are we connected?
  if (client_connect(domiqBaseIp, 4224)){
    Serial.println(F("Domiq connection established."));
    connectionEstablished = TRUE;
  }
  else{
    // Warn if the connection wasn't made
    Serial.println(F("Connection failed, trying again."));
  }

  //Save the time.
  LastReceivedDataAtTime = millis();

  return connectionEstablished;
}


void TCP_SERVER::send_data(String &Data)
{
  if(Data.length() > 0){
    // Make a HTTP request:
    client_println(Data);

    DEBUG_DATA::tcp_server_print_send_new_data(Data);
  }
}


void TCP_SERVER::loop()
{
  bool8 dataReceived = client_read_multibyte_data();

  if(dataReceived == TRUE){
    //Save the time.
    LastReceivedDataAtTime = millis();

    DEBUG_DATA::tcp_server_print_command_received(ReceivedData);
  }
  else{
    //No data received. Something is wrong. Check the time.
    if((millis() - LastReceivedDataAtTime) > TCP_IP_SETTINGS_TIMEOUT_IN_MS){
      ReconnectCounter++;
      
      Serial.print(F("Timeout, reastablishing connection: "));
      Serial.println(ReconnectCounter);

      //Stop this client.
      client_stop();

      //Reconnect to domiq base.
      connect_to_domiq();
    }
  }

  // If the server disconnected, then stop the client:
  if (!client_connected()){
    ReconnectCounter++;
    Serial.print(F("Server disconnected. Trying to restart: "));
    Serial.println(ReconnectCounter);

    //Stop this client.
    client_stop();

    //Reconnect to domiq base.
    connect_to_domiq();
  }
}

bool8 TCP_SERVER::client_read_multibyte_data(void)
{
  int dataLength;
  bool8 dataReceived = FALSE;
  bool8 lineCarriageFound = FALSE;

  //Copy the last received values to the received data.
  ReceivedData = TempReceiveBuffer;
  
  #ifdef DEBUG_DATA_TCP_SERVER
  if(TempReceiveBuffer.length() > 0u){
    Serial.print(F("TCP server Temp buffer is filled with: "));
    Serial.println(TempReceiveBuffer);
  }
  #endif

  //Empty the temp receive buffer.
  TempReceiveBuffer = "";

  do{
    //Call the client read function.
    dataLength = client_read(buffer, TCP_SERVER_CLIENT_READ_MULTIBYTE_BUFFER_SIZE);

    if(dataLength > 0){
      //Convert the data to a string. Avoid that the string overflows.
      //Do one message after another.
      lineCarriageFound = copy_received_char_array_to_string((Uint8)dataLength);

      dataReceived = TRUE;
    }
    else{
      //Break the while loop.
      lineCarriageFound = TRUE;
    }
  }while((dataLength > 0) && (lineCarriageFound == FALSE));

  return dataReceived;
}


bool8 TCP_SERVER::copy_received_char_array_to_string(Uint8 Size)
{
  Uint8 i;
  bool8 lineCarriageFound = FALSE;

  for(i = 0u; i < Size; i++){
    if(lineCarriageFound == FALSE){
      //Add the data to the received data. Check if carriage return was found.
      ReceivedData += (char)buffer[i];
    }
    else{
      TempReceiveBuffer += (char)buffer[i];
    }

    if(buffer[i] == '\n'){
      //Line carriage found.
      lineCarriageFound = TRUE;
    }
  }

  return lineCarriageFound;
}
