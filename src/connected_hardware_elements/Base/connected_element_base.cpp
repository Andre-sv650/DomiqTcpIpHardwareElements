

#include "connected_element_base.h"
#include "connected_element_array.h"
#include <Arduino.h>

/*
 * Constructor
 */
CONNECTED_ELEMENT_BASE::CONNECTED_ELEMENT_BASE()
{
  Pin = 0;
}

//Initiate method without pin, for example for I2C sensors
void CONNECTED_ELEMENT_BASE::initiate(const String &VarElementNameInDomiq)
{
  this->VarNameInDomiq = VarElementNameInDomiq;
}


void CONNECTED_ELEMENT_BASE::initiate(Uint8 Pin, const String &VarElementNameInDomiq)
{
  CONNECTED_ELEMENT_BASE::initiate(Pin, VarElementNameInDomiq, (Uint8)0u);
}

/*  Initiate the element with a priority
*   VarElementNameInDomiq The element name in domiq base
*   PriorityLevel The priority level. A higher value means higher priority.
*/
void CONNECTED_ELEMENT_BASE::initiate(Uint8 Pin, const String &VarElementNameInDomiq, Uint8 PriorityLevel)
{
  this->Pin = Pin;
  VarNameInDomiq = VarElementNameInDomiq;
  this->SampledValue = "";;
  this->NewDataSampled = TRUE;

  //Set this to the connected elements array.
  CONNECTED_ELEMENT_ARRAY::add_element(this);


  
}


void CONNECTED_ELEMENT_BASE::get_sampled_data(String &Result)
{
  //New data was received. Generate the domiq string.
  generate_domiq_string(this->SampledValue, Result);
}

void CONNECTED_ELEMENT_BASE::set_data_from_domiq(String &Value)
{
    //For all elements without set data function.
  if(this->ReceivedDataFromDomiq.compareTo(Value) != 0){
    //New data detected.
    this->ReceivedDataFromDomiq = Value;
    this->NewDataReceived = TRUE;
  }
}

void CONNECTED_ELEMENT_BASE::background_routine(void)
{
  
}

void CONNECTED_ELEMENT_BASE::set_new_data_sampled(String &Value)
{
  //For all elements without set data function.
  if(this->SampledValue.compareTo(Value) != 0){
    //New data detected.
    this->SampledValue = Value;
    this->NewDataSampled = TRUE;

    debug_message_new_sampled_data();
  }
}


//Protected routines
void CONNECTED_ELEMENT_BASE::generate_domiq_string(float32 Value, String &Result)
{
  String valueString = String(Value);

  generate_domiq_string(valueString, Result);
}


void CONNECTED_ELEMENT_BASE::generate_domiq_string(Uint8 Value, String &Result)
{
  String valueString = String(Value);

  generate_domiq_string(valueString, Result);
}


void CONNECTED_ELEMENT_BASE::generate_domiq_string(String &VarName, float32 Value, String &Result)
{
  Result += VarName + "=" + String(Value) + "\r\n";
}


void CONNECTED_ELEMENT_BASE::generate_domiq_string(String &Value, String &Result)
{
  Result += VarNameInDomiq + "=" + Value + "\r\n";
}



void CONNECTED_ELEMENT_BASE::debug_message_new_sampled_data(void)
{
    debug_message_new_sampled_data(VarNameInDomiq, SampledValue);
}


//New data to domiq sending, generate a message in the console.
void CONNECTED_ELEMENT_BASE::debug_message_new_sampled_data(String &VariableNameInDomiq, String &SampledValueFromArduino)
{
  #ifdef DEBUG_CONNECTED_ELEMENT_BASE_MESSAGES_TO_DOMIQ
    
  Serial.print(F("Data sampled for variable: "));
  Serial.print(VariableNameInDomiq);
  Serial.print(F(". Data: "));
  Serial.println(SampledValueFromArduino);

  #endif
}

//New data from domiq received, generate a message in the console.
void CONNECTED_ELEMENT_BASE::debug_message_new_data_from_domiq(void)
{
  #ifdef DEBUG_CONNECTED_ELEMENT_BASE_MESSAGES_FROM_DOMIQ

  Serial.print(F("Data received from Domiq: "));
  Serial.print(VarNameInDomiq);
  Serial.print(F(". Data: "));
  Serial.println(ReceivedDataFromDomiq);

  #endif
}


