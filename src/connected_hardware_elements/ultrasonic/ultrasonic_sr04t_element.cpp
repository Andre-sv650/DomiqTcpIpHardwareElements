
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
  pinMode(EchoPin, INPUT);

  //Set the last sample time to sample the first value.
  LastSampleTime = millis() - ULTRASONIC_SR04T_ELEMENT_SAMPLE_TIME;

  CONNECTED_ELEMENT_BASE::initiate(TriggerPin, VarNameInDomiq);
}

//Background routine for the light intensity.
void ULTRASONIC_SR04T_ELEMENT::background_routine()
{
  if((millis() - LastSampleTime) > ULTRASONIC_SR04T_ELEMENT_SAMPLE_TIME){
    #ifdef DEBUG_SR04T_ELEMENT
    Serial.println(F("Ultrasonic element starting."));
    #endif

    Uint32 duration;
    Uint16 distanceInCm;

    //Clear the trigPin by setting it LOW
    digitalWrite(this->Pin, LOW);
    delayMicroseconds(5);
    
    //Disturb the interrupts, because otherwise the counting is not done correctly.
    noInterrupts();

    //Trigger the sensor by setting the trigPin high for 10 microseconds
    digitalWrite(this->Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->Pin, LOW);
    //Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds.
    //Set the maximum length to 100000us = 100ms, this should be enough to measrure the length.
    //0,343 km/s is the normal speed. This is 0.43m /ms. With 50ms the maximum is 22m.
    duration = pulseIn(this->EchoPin, HIGH, 50000);

    //Enable the interrupts.
    interrupts();

    //Calculate the distance. Duration * 0.034 / 2 is the normal calculation. Set it up to non floating point, this is faster.
    distanceInCm = (Uint16)(duration / 59);

    //Filter the value.
    Uint16 newDistanceInCm = Filter.filter_value(distanceInCm);
    String newDistance = String(newDistanceInCm);

    //Set the sampled data.
    CONNECTED_ELEMENT_BASE::set_new_data_sampled(newDistance);

    //Save the last sample time.
    LastSampleTime = millis();

    #ifdef DEBUG_SR04T_ELEMENT
    Serial.print(F("Ultrasonic element ended. New distance: "));
    Serial.println(newDistance);
    #endif
  }
}

#endif //ULTRASONIC_SR04T_ELEMENT_ENABLED