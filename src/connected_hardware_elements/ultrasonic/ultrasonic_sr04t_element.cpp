
#include "ultrasonic_sr04t_element.h"
#include "Arduino.h"
#ifdef ULTRASONIC_SR04T_ELEMENT_ENABLED

//Default constructor.
ULTRASONIC_SR04T_ELEMENT::ULTRASONIC_SR04T_ELEMENT()
{
}

/*
 * Ultrasonic sensor.
 */
void ULTRASONIC_SR04T_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 TriggerPin, Uint8 EchoPin)
{
  this->EchoPin = EchoPin;

  //Define inputs and outputs
  pinMode(TriggerPin, OUTPUT);

  //Put a pull up at the echo pin, otherwise the measurement is not stable.
  //This was answered in https://forum.arduino.cc/index.php?topic=474759.0.
  pinMode(EchoPin, INPUT_PULLUP);

  //Set the last sample time to sample the first value.
  LastSampleTime = millis() - ULTRASONIC_SR04T_ELEMENT_SAMPLE_TIME;

  CONNECTED_ELEMENT_BASE::initiate(TriggerPin, VarNameInDomiq);
}

//Background routine for the light intensity.
void ULTRASONIC_SR04T_ELEMENT::background_routine()
{
  if((millis() - LastSampleTime) > ULTRASONIC_SR04T_ELEMENT_SAMPLE_TIME){
    //The echo pin has to be false, otherwise starting a new sample is invalid.
    if(digitalRead(this->EchoPin) == FALSE){
      #ifdef DEBUG_SR04T_ELEMENT
      Serial.print(F("Ultrasonic element starting. "));
      Serial.println(VarNameInDomiq);
      #endif

      Uint32 duration;
      Uint16 distanceInCm;

      //Disturb the interrupts, because otherwise the counting is not done correctly.
      noInterrupts();

      //Clear the trigPin by setting it LOW. Normally not needed, but to be on the safe side.
      digitalWrite(this->Pin, LOW);
      delayMicroseconds(30);

      //Trigger the sensor by setting the trigPin high for 10 microseconds
      digitalWrite(this->Pin, HIGH);

      //Hold the pin high for more than 10us. We are using 30us to be on the safe side.
      //SR04T is not stable enough for 10us.
      delayMicroseconds(30);

      //Start the measurement of the distance.
      digitalWrite(this->Pin, LOW);

      //Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds.
      //Set the maximum length to 100000us = 100ms, this should be enough to measrure the length.
      //0,343 km/s is the normal speed. This is 0.43m /ms. With 50ms the maximum is 22m.
      duration = pulseIn(this->EchoPin, HIGH);

      //Enable the interrupts.
      interrupts();

      //Check if the duration is greater than 0, otherwise the time out was reached.
      if(duration > 0){
        //Calculate the distance. Duration * 0.034 / 2 is the normal calculation. 
        //Set it up to non floating point, this is faster.
        distanceInCm = (Uint16)(duration / 59);

        //Filter the value.
        Uint16 newDistanceInCm = Filter.filter_value(distanceInCm, 1, ULTRASONIC_SR04T_ELEMENT_FILTER_VALUE);
        String newDistance = String(newDistanceInCm);

        #ifdef DEBUG_SR04T_ELEMENT
        Serial.print(this->VarNameInDomiq);
        Serial.print(F(" ended. New duration: "));
        Serial.print(duration);
        Serial.print(F(". New filtered distance: "));
        Serial.println(newDistance);
        #endif

        //Set the sampled data.
        CONNECTED_ELEMENT_BASE::set_new_data_sampled(newDistance);

        //Save the last sample time.
        LastSampleTime = millis();
      }
    }
  }
}

#endif //ULTRASONIC_SR04T_ELEMENT_ENABLED