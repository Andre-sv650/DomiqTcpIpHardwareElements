
#include "connected_element_array.h"

namespace CONNECTED_ELEMENT_ARRAY
{
Uint8 BackgroundRoutineCounter;
/*
   * The registered elements.
   */
CONNECTED_ELEMENT_BASE *pRegisteredElements[CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH];

/*
   * The size in bits.
   */
Uint8 RegisteredElementsCount;

void initiate(void)
{
  RegisteredElementsCount = 0u;
  BackgroundRoutineCounter = 0u;
}


void add_element(CONNECTED_ELEMENT_BASE *pNewElement)
{
  //Set the element.
  if (RegisteredElementsCount < CONNECTED_ELEMENT_ARRAY_ELEMENTS_LENGTH)
  {
    pRegisteredElements[RegisteredElementsCount] = pNewElement;

    RegisteredElementsCount++;

    DEBUG_DATA::connected_element_array_item_added(TRUE);
  }
  else
  {
    DEBUG_DATA::connected_element_array_item_added(FALSE);
  }
}

/*
 * Get the element from the requested address.
 */
void set_new_data_from_domiq(String &DataWithVarNameAndValue)
{
  Uint8 dataLength = DataWithVarNameAndValue.length();
  
  if (dataLength > 0)
  {
    int indexOfGleich = DataWithVarNameAndValue.indexOf("=");

    if (indexOfGleich > 0)
    {
      Uint8 i;
      String VariableName = DataWithVarNameAndValue.substring(0, indexOfGleich);
      String Value = DataWithVarNameAndValue.substring(indexOfGleich + 1, dataLength - 1);
            
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
}

String get_new_data()
{
  String newData;

  //Call all elements in this.
  for (Uint8 i = 0u; i < RegisteredElementsCount; i++)
  {
    //Check if the data changed.
    if(pRegisteredElements[i]->NewDataSampled == TRUE){
      //Call the routine to get the new data.
      String dataFromElement = pRegisteredElements[i]->get_sampled_data();
      newData += dataFromElement;

      DEBUG_DATA::connected_element_array_found_new_data(pRegisteredElements[i]->VarNameInDomiq, dataFromElement);

      pRegisteredElements[i]->NewDataSampled = FALSE;
    }
  }

  return newData;
}

void background_routine(void)
{
  if(BackgroundRoutineCounter < RegisteredElementsCount){
    BackgroundRoutineCounter++;
  }
  else{
    
  }

  BackgroundRoutineCounter = 1u;
    
  //Call the routine.
  pRegisteredElements[BackgroundRoutineCounter]->background_routine();
}


} // namespace CONNECTED_ELEMENT_ARRAY
