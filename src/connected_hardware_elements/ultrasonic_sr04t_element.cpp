
#include "ultrasonic_sr04t_element.h"
#ifdef ULTRASONIC_SR04T_ELEMENT_ENABLED
#include "../debug/debug_data.h"


//Default constructor.
ULTRASONIC_SR04T_ELEMENT::ULTRASONIC_SR04T_ELEMENT()
{
}

/*
 * Ligth intensity element. Connect VCC with 5V, GND with GND.
 * On arduino uno connect SCL with PIN A5 and SDA with PIN A4.
 * On arduino mega connect SCL with Pin Pin 21 and SDA with PIN 20.
 * See https://www.arduino.cc/en/Reference/Wire for details.
 */
void ULTRASONIC_SR04T_ELEMENT::initiate(const String &VarNameInDomiq, Uint8 TriggerPin, Uint8 EchoPin)
{
  this->Pin = TriggerPin;

  //Define inputs and outputs
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  this->EchoPin = EchoPin;

  CONNECTED_ELEMENT_BASE::initiate(VarNameInDomiq);
}

//Background routine for the light intensity.
void ULTRASONIC_SR04T_ELEMENT::background_routine()
{
  long duration;
  Uint16 distanceInCm;
  
  //Clear the trigPin by setting it LOW
  digitalWrite(this->Pin, LOW);
  delayMicroseconds(5);
  //Trigger the sensor by setting the trigPin high for 10 microseconds
  digitalWrite(this->Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->Pin, LOW);
  //Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds.
  duration = pulseIn(this->EchoPin, HIGH);
  // Calculate the distance
  distanceInCm= duration*0.034/2;

  //Filter the value.
  Uint16 newDistanceInCm = Filter.filter_value(distanceInCm, 1, 1);
  String newDistance = String(newDistanceInCm);

  //Set the sampled data.
  CONNECTED_ELEMENT_BASE::set_new_data_sampled(newDistance);
}

#endif //ULTRASONIC_SR04T_ELEMENT_ENABLED