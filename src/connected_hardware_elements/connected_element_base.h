

#ifndef CONNECTED_ELEMNTS_BASE_H
#define CONNECTED_ELEMNTS_BASE_H

#include "../datatypes/cpu_datatypes.h"
#include "../debug/debug_data.h"
#include <WString.h>

/*
 * One element
 */
class CONNECTED_ELEMENT_BASE
{
  #define CONNECTED_ELEMENT_BASE_ARRAY_SIZE 4

  //Members
public:  
  /*
   * The pin on the arduino.
   */
  Uint8 Pin;

  String VarNameInDomiq;

  String SampledValue;

  String ReceivedDataFromDomiq;

  //New data was sampled by the arduino
  bool8 NewDataSampled;
  //New data was set by domiq base.
  bool8 NewDataReceived;

  /*
   * Methods
   */
public:
  CONNECTED_ELEMENT_BASE();

  void initiate(const String &VarElementNameInDomiq);

  void initiate(Uint8 Pin, const String &VarElementNameInDomiq);

  void initiate(const String &VarElementNameInDomiq, Uint8 PriorityLevel);

  virtual void background_routine(void);

  virtual String get_sampled_data(void);

  virtual void set_data_from_domiq(String &Value);

  virtual void set_new_data_sampled(String &Value);

  protected:
    String generate_domiq_string(float32 Value);

    String generate_domiq_string(Uint8 Value);

    String generate_domiq_string(String VarName, float32 Value);

    String generate_domiq_string(String Value);


  private:
    void debug_message_new_sampled_data(void);

    void debug_message_new_data_from_domiq(void);
};




#endif /* MODBUS_ELEMENT_BASE_H_ */
