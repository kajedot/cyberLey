#ifndef DRINKING_SENSOR_H__
#define DRINKING_SENSOR_H__

#define SENSOR_RATIO  4.8 // Hz to l/min
#define BUFFER_LEN 10     // number of data blocks (1 blk = 1 ulong)
#define BUFFER_START 0x10 // EEPROM address where buffer starts

#include "eewl.h"

class DrinkingSensor
{
    private:

    static void count();

    int inputPin = 2;
    unsigned int timedOut = 50;
  
    public:

    void setTimedOut(unsigned int timedOut); // default 50 [ms]
    void init(int inputPin); // digital interrupt pin number (default 2)
    void zero();
    void saveCycle();

    float getVelocity(); // [l/min]
    float getMaxVelocity(); // [l/min]
    float getAverageVelocity(); // [l/min]
    float getVolume(); // [l]
    float getCycle(); // [l]
};

#endif
