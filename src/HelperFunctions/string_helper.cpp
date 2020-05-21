#include "string_helper.h"
#include <WString.h>

namespace STRING_HELPER_FUNCTIONS
{
void get_line(String& Data, String &Result)
{
    const String delimiter = "\n";
    int pos = Data.indexOf(delimiter);

    if(pos > 0){
        //Get the token.
        Result = Data.substring(0, pos);

        Data.remove(0u, pos);
    }
    else{
        //Delete the string.
        Result = "";
    }
}
} // namespace STRING_HELPER_FUNCTIONS