/* DHT library
MIT license
written by Adafruit Industries
 */

#include "../AllYouNeedIsStartHere/project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

#ifndef DHT_H
#define DHT_H

#include "../datatypes/cpu_datatypes.h"
#include "Arduino.h"

// Uncomment to enable printing out nice debug messages.
//#define DHT_DEBUG

// Define where debug output will be printed.
//#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef DHT_DEBUG
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define DEBUG_PRINT(...) {}
#define DEBUG_PRINTLN(...) {}
#endif

// Define types of sensors.
// Define types of sensors.
#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21


class DHT
{

public:
  DHT(void);
  
  void begin(Uint8 pin, Uint8 type, Uint8 count=6);
  float32 readTemperature(bool S=false, bool force=false);
  float32 convertCtoF(float32);
  float32 convertFtoC(float32);
  float32 computeHeatIndex(float32 temperature, float32 percentHumidity, bool isFahrenheit=true);
  float32 readHumidity(bool force=false);
  boolean read(bool force=false);

private:
  uint8_t data[5];
  uint8_t _pin, _type;
#ifdef __AVR
  // Use direct GPIO access on an 8-bit AVR so keep track of the port and bitmask
  // for the digital pin connected to the DHT.  Other platforms will use digitalRead.
  uint8_t _bit, _port;
#endif
  uint32_t _lastreadtime, _maxcycles;
  bool _lastresult;

  Uint32 expectPulse(bool level);
};




class InterruptLock {
public:
  InterruptLock() {
    noInterrupts();
  }
  ~InterruptLock() {
    interrupts();
  }
};

#endif //DHT_H

#endif //#ifdef DHT22_ELEMENT_ENABLED
