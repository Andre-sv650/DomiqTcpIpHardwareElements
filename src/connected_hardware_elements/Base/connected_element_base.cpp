

#include "connected_element_base.h"
#include "connected_element_array.h"

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
  CONNECTED_ELEMENT_BASE::initiate((Uint8)0, VarElementNameInDomiq);
}


void CONNECTED_ELEMENT_BASE::initiate(Uint8 Pin, const String &VarElementNameInDomiq)
{
  this->Pin = Pin;
  VarNameInDomiq = VarElementNameInDomiq;
  this->NewDataSampled = TRUE;

  //Set this to the connected elements array.
  CONNECTED_ELEMENT_ARRAY::add_element(this);
}

/*  Initiate the element with a priority
*   VarElementNameInDomiq The element name in domiq base
*   PriorityLevel The priority level. A higher value means higher priority.
*/
void CONNECTED_ELEMENT_BASE::initiate(const String &VarElementNameInDomiq, Uint8 PriorityLevel)
{
  VarNameInDomiq = VarElementNameInDomiq;
}


String CONNECTED_ELEMENT_BASE::get_sampled_data(void)
{
  //New data was received. Generate the domiq string.
  return generate_domiq_string(this->SampledValue);
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
String CONNECTED_ELEMENT_BASE::generate_domiq_string(float32 Value)
{
  return generate_domiq_string(String(Value));
}


String CONNECTED_ELEMENT_BASE::generate_domiq_string(Uint8 Value)
{
  return generate_domiq_string(String(Value));
}


String CONNECTED_ELEMENT_BASE::generate_domiq_string(String VarName, float32 Value)
{
  String returnValue = VarName + "=" + String(Value) + "\r\n";

  return returnValue;
}


String CONNECTED_ELEMENT_BASE::generate_domiq_string(String Value)
{
  String returnValue = VarNameInDomiq + "=" + Value + "\r\n";

  return returnValue;
}



void CONNECTED_ELEMENT_BASE::debug_message_new_sampled_data(void)
{
    debug_message_new_sampled_data(VarNameInDomiq, SampledValue);
}


void CONNECTED_ELEMENT_BASE::debug_message_new_sampled_data(const String &VariableNameInDomiq, const String &SampledValueFromArduino)
{
    String newSampledData = "New data sampled for variable: " + VariableNameInDomiq + ". Pin:" + Pin + ". Data: " + SampledValueFromArduino;
    DEBUG_DATA::generic_send_debug_message(newSampledData); 
}


void CONNECTED_ELEMENT_BASE::debug_message_new_data_from_domiq(void)
{
    String newDataFromDomiq = "New data from domiq received: " + VarNameInDomiq + ". Pin:" + Pin + ". Data: " + ReceivedDataFromDomiq;
    DEBUG_DATA::generic_send_debug_message(newDataFromDomiq); 
}

