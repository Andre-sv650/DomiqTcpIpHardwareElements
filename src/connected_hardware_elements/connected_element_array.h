#ifndef CONNECTED_ELEMENT_ARRAY_H
#define CONNECTED_ELEMENT_ARRAY_H

#include "../AllYouNeedIsStartHere/project_defines.h"
#include "../datatypes/cpu_datatypes.h"
#include "../debug/debug_data.h"
#include "connected_element_base.h"

/*
 * The array containing all modbus elements.
 */
namespace CONNECTED_ELEMENT_ARRAY
{
   //Methods
   void initiate(void);

   void background_routine(void);
   
   void add_element(CONNECTED_ELEMENT_BASE *pNewElement);

   void set_new_data_from_domiq(String &DataWithVarNameAndValue);

   void set_new_data_from_domiq_internal(String &Line);

   String get_new_data(void);
};


#endif /* CONNECTED_ELEMENT_ARRAY_H_ */
