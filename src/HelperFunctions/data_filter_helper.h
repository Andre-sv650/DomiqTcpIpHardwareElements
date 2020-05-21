
#ifndef DATA_FILTER_HELPER_H
#define DATA_FILTER_HELPER_H

#include "datatypes/cpu_datatypes.h"

//See https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp for example.

template <class T>
class DATA_FILTER_HELPER
{
  private:
    T LastValue;

    bool8 StartOfMeasurement;

    T SampledValues[DATA_FILTER_HELPER_ARRAY_LENGTH];

    Uint8 SampledValueIndex;

  public:
    
    DATA_FILTER_HELPER()
    {
        StartOfMeasurement = TRUE;

        SampledValueIndex = 0u;
    }

    //Filter the value with the Value difference and the number of time.
    T filter_value(T NewValue, T ValueDifference, Uint8 NumberOfTimes)
    {
        float32 result = 0.0f;
        //Increment the index.
        SampledValueIndex++;
        //Check if index is valid.
        if(SampledValueIndex >= DATA_FILTER_HELPER_ARRAY_LENGTH){
            SampledValueIndex = 0u;
        }

        //Save the new sampled
        SampledValues[SampledValueIndex] = NewValue;

        for(Uint8 i = 0u; i < DATA_FILTER_HELPER_ARRAY_LENGTH; i++){
           if(StartOfMeasurement == TRUE){
               SampledValues[i] = NewValue;
           }

           result += (float32)SampledValues[i];
        }

        StartOfMeasurement = FALSE;

        return (T)(result / (float32)DATA_FILTER_HELPER_ARRAY_LENGTH);
    }
};

#endif
