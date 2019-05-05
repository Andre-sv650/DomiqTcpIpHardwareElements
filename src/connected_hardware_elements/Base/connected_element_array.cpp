
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
Uint8 RegisteredElementsWithPriority;

void initiate(void)
{
  Uint8 i;
  RegisteredElementsCount = 0u;
  RegisteredElementsWithPriority = 0u;
  BackgroundRoutineCounter = 0u;

  for (i = 0u; i < CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH; i++)
  {
    pRegisteredElements[i] = NULL_PTR;
    pRegisteredElementsWithPriority[i] = NULL_PTR;
  }

  Serial.println("Array elements initiated");
}

//Add one element to the array.
void add_element(CONNECTED_ELEMENT_BASE *pNewElement)
{
  //Set the element.
  if (RegisteredElementsCount < CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH)
  {
    pRegisteredElements[RegisteredElementsCount] = pNewElement;

    RegisteredElementsCount++;

    DEBUG_DATA::connected_element_array_item_added(pNewElement->VarNameInDomiq);
  }
}

//Add one element with priority.
void add_element(CONNECTED_ELEMENT_BASE *pNewElement, Uint8 PriorityLevel)
{

}

/*
 * Get the element from the requested address.
 */
void set_new_data_from_domiq(String &DataWithVarNameAndValue)
{
  Uint8 dataLength = DataWithVarNameAndValue.length();

  if (dataLength > 0)
  {
    String line;
    int lineLength = 0;

    do
    {
      line = STRING_HELPER_FUNCTIONS::get_line(DataWithVarNameAndValue);
      lineLength = line.length();

      if (lineLength > 0)
      {
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

  if (indexOfGleich > 0)
  {
    Uint8 i;
    String VariableName = Line.substring(0, indexOfGleich);
    String Value = Line.substring(indexOfGleich + 1, dataLength - 1);

    for (i = 0u; i < RegisteredElementsCount; i++)
    {
      //Check if this is the element.
      if (VariableName.compareTo(pRegisteredElements[i]->VarNameInDomiq) == 0)
      {
        DEBUG_DATA::connected_element_array_item_found_setting_data(VariableName, Value);
        pRegisteredElements[i]->set_data_from_domiq(Value);

        //Data was set. Return from the function.
        return;
      }
    }
  }
}

String get_new_data()
{
  String newData;

  //Call all elements in this.
  for (Uint8 i = 0u; i < RegisteredElementsCount; i++)
  {
    //Check if the data changed.
    if (pRegisteredElements[i]->NewDataSampled == TRUE)
    {
      //Call the routine to get the new data.
      String dataFromElement = pRegisteredElements[i]->get_sampled_data();
      newData += dataFromElement;

      DEBUG_DATA::connected_element_array_found_new_data(pRegisteredElements[i]->VarNameInDomiq, dataFromElement);

      pRegisteredElements[i]->NewDataSampled = FALSE;
    }
  }

  return newData;
}

//The background routine.
void background_routine(void)
{
  BackgroundRoutineCounter++;

  if (BackgroundRoutineCounter >= RegisteredElementsCount)
  {
    BackgroundRoutineCounter = 0;
  }

  //Check if element is not NULL_PTR to avoid calling a not available function and resetting the arduino.
  if (pRegisteredElements[BackgroundRoutineCounter] != NULL_PTR)
  {
    //Call the routine.
    pRegisteredElements[BackgroundRoutineCounter]->background_routine();
  }

  //Do all registered elements with priority.
  for(Uint8 i = 0u; i < RegisteredElementsWithPriority; i++){
    //Call each background routine.
    pRegisteredElementsWithPriority[i]->background_routine();
  }
}

} // namespace CONNECTED_ELEMENT_ARRAY
