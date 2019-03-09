#include "string_helper.h"
#include <WString.h>

namespace STRING_HELPER_FUNCTIONS
{
String get_line(String& Data)
{
    const String delimiter = "\n";
    int pos = Data.indexOf(delimiter);
    String token;

    if(pos > 0){
        //Get the token.
        token = Data.substring(0, pos);

        Data.remove(0u, pos);
    }
    
    return token;
}
} // namespace STRING_HELPER_FUNCTIONS