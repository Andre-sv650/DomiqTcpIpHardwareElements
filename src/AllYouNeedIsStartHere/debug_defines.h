#ifndef DEBUG_DEFINES_H
#define DEBUG_DEFINES_H

//Section TCP server
//#define DEBUG_DATA_TCP_SERVER //Reports all incoming messages from the TCP/IP interface that are received from or send to domiq.
#define DEBUG_DATA_SENSOR_ELEMENTS_ALL //Reports incoming and outgoing data from the sensors that are connected.

//Section: Base debug define. This enables all messages that are outgoing to domiq base.
//Enable the switch for debugging. Disable it to be faster and use less time for sending data to the console of visual studio code.
//This is making a hughe difference in performance. So only use it if something is not working how it is expected.
#define DEBUG_CONNECTED_ELEMENT_BASE_MESSAGES_TO_DOMIQ
#define DEBUG_CONNECTED_ELEMENT_BASE_MESSAGES_FROM_DOMIQ

//Section Connected element array
//#define DEBUG_CONNECTED_ELEMENT_ARRAY

//Section Relay
#define DEBUG_RELAIS_SET
#define DEBUG_RELAIS_GET

//Section DHT22 sensor
#define DEBUG_DHT22

//Section One wire sensor
//#define DEBUG_TEMP_SENSOR_ONE_WIRE

//Section light intensity element
//#define DEBUG_LIGHT_INTENSITY_ELEMENT

//Section the ultrasonic sr04 t element debug.
//#define DEBUG_SR04T_ELEMENT

//Section presence detector element
//#define DEBUG_PRESENCE_DETECTOR_ELEMENT

//Debug for the interrupt element
#define DEBUG_INTERRUPT_ELEMENT

//The debug for the RC switch element.
#define DEBUG_RC_SWITCH_ELEMENT
#define DEBUG_RC_SENDER_ELEMENT

#endif /* MODBUS_DEBUG_DEFINES_H */
