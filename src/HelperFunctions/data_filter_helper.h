
#ifndef DATA_FILTER_HELPER_H
#define DATA_FILTER_HELPER_H

#include "datatypes/cpu_datatypes.h"

//See https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp for example.

template <class T>
class DATA_FILTER_HELPER
{
  private:
    T LastValue;

    Uint8 DifferenceCounter;

  public:
    
    DATA_FILTER_HELPER()
    {

    }

    //Filter the value with the Value difference and the number of time.
    T filter_value(T NewValue, T ValueDifference, Uint8 NumberOfTimes)
    {
        T result;

        if (NewValue > LastValue + ValueDifference)
        {
            DifferenceCounter++;
        }
        else if (NewValue < LastValue - ValueDifference)
        {
            DifferenceCounter++;
        }
        else
        {
            DifferenceCounter = 0u;
        }

        if (DifferenceCounter > NumberOfTimes)
        {
            result = NewValue;
            LastValue = NewValue;

            DifferenceCounter = 0;
        }
        else
        {
            result = LastValue;
        }

        return result;
    }


};

#endif
