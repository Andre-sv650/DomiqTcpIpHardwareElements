
#include "connected_element_array.h"
#include "Arduino.h"
#include "../../HelperFunctions/string_helper.h"

namespace CONNECTED_ELEMENT_ARRAY
{
Uint8 BackgroundRoutineCounter;
/*
   * The registered elements.
   */
CONNECTED_ELEMENT_BASE *pRegisteredElements[CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH];

/*
*  The registered elements that has a higher priority.
*/
CONNECTED_ELEMENT_BASE *pRegisteredElementsWithPriority[CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH];

/*
   * The size in bits.
   */
Uint8 RegisteredElementsCount;

//The priority elements.
Uint8 RegisteredElementsWithPriorityCount;

void initiate(void)
{
  Uint8 i;
  RegisteredElementsCount = 0u;
  RegisteredElementsWithPriorityCount = 0u;
  BackgroundRoutineCounter = 0u;

  for (i = 0u; i < CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH; i++){
    pRegisteredElements[i] = (CONNECTED_ELEMENT_BASE*)NULL_PTR;
    pRegisteredElementsWithPriority[i] = (CONNECTED_ELEMENT_BASE*)NULL_PTR;
  }

  #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY
  Serial.println(F("Array elements initiated"));
  #endif
}

//Add one element to the array.
void add_element(CONNECTED_ELEMENT_BASE *pNewElement)
{
  //Set the element.
  if (RegisteredElementsCount < CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH){
    pRegisteredElements[RegisteredElementsCount] = pNewElement;

    RegisteredElementsCount++;

    DEBUG_DATA::connected_element_array_item_added(pNewElement->VarNameInDomiq);
  }
}

//Add one element with priority.
void add_element(CONNECTED_ELEMENT_BASE *pNewElement, Uint8 PriorityLevel)
{
  pRegisteredElementsWithPriority[RegisteredElementsWithPriorityCount] = pNewElement;

  RegisteredElementsWithPriorityCount++;

  DEBUG_DATA::connected_element_array_item_added(pNewElement->VarNameInDomiq);
}

/*
 * Get the element from the requested address.
 */
void set_new_data_from_domiq(String &DataWithVarNameAndValue)
{
  Uint8 dataLength = DataWithVarNameAndValue.length();

  if (dataLength > 0){
    //Delete the old string.
    int lineLength = 0;
    String line;

    do{
      STRING_HELPER_FUNCTIONS::get_line(DataWithVarNameAndValue, line);
      lineLength = line.length();

      if (lineLength > 0){
        set_new_data_from_domiq_internal(line);
      }
    } while (lineLength > 0);
  }
}



void set_new_data_from_domiq_internal(String &Line)
{
  int indexOfGleich = Line.indexOf("=");
  int dataLength = Line.length();
  
  #ifdef DEBUG_CONNECTED_ELEMENT_ARRAY
  Serial.println("Line found: " + Line);
  #endif

  if ((indexOfGleich > 0) && ((indexOfGleich + 1) < dataLength)){
    Uint8 i;
    String VariableName = Line.substring(0u, (unsigned int)indexOfGleich);
    String Value = Line.substring((unsigned int)indexOfGleich + 1u, (unsigned int)dataLength - 1u);

    for(i = 0u; i < RegisteredElementsCount; i++){
      //Check if this is the element.
      if (VariableName.compareTo(pRegisteredElements[i]->VarNameInDomiq) == 0){
        DEBUG_DATA::connected_element_array_item_found_setting_data(VariableName, Value);
        
        //Set the data.
        pRegisteredElements[i]->set_data_from_domiq(Value);

        //Data was set. Return from the function.
        return;
      }
    }
  }
}

void get_new_data(String &Result)
{
  //Delte result
  Result = "";

  //Call all elements in this.
  for (Uint8 i = 0u; i < RegisteredElementsCount; i++){
    //Check if the data changed.
    if (pRegisteredElements[i]->NewDataSampled == TRUE){
      //Call the routine to get the new data.
      pRegisteredElements[i]->get_sampled_data(Result);

      //Delete the flag.
      pRegisteredElements[i]->NewDataSampled = FALSE;

      //send one data at one time to avoid messages which are too long.
      return;
    }
  }

  DEBUG_DATA::connected_element_array_found_new_data(Result);
}

//The background routine.
void background_routine(void)
{
  Uint8 i;
  BackgroundRoutineCounter++;

  if (BackgroundRoutineCounter >= RegisteredElementsCount){
    BackgroundRoutineCounter = 0;
  }

  //Check if element is not NULL_PTR to avoid calling a not available function and resetting the arduino.
  if (pRegisteredElements[BackgroundRoutineCounter] != NULL_PTR){
    //Call the routine.
    pRegisteredElements[BackgroundRoutineCounter]->background_routine();
  }

  //Do all registered elements with priority.
  for(i = 0u; i < RegisteredElementsWithPriorityCount; i++){
    //Call each background routine.
    pRegisteredElementsWithPriority[i]->background_routine();
  }
}

} // namespace CONNECTED_ELEMENT_ARRAY
