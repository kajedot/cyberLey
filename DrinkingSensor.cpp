#include <Arduino.h>
#include <DrinkingSensor.h>

volatile unsigned int prevTime = 0;
volatile float velocity = 0;
volatile float volume = 0;
volatile float maxVelocity = 0;
volatile float averageVelocity = 0;
volatile unsigned long long counter = 1;

volatile unsigned long lastCycle = 0;
volatile unsigned long eepromCycle = 0;

EEWL eeprom(eepromCycle, BUFFER_LEN, BUFFER_START);

void DrinkingSensor::count()
{
    unsigned int curTime = millis();
    float dt = float(curTime - prevTime)/1000;
    velocity = 1 / dt / SENSOR_RATIO;  // [l/min]
    volume += velocity / 60 * dt;
    prevTime = curTime;
    
    averageVelocity += velocity;
    counter++;

    if(velocity > maxVelocity)
    {
        maxVelocity = velocity;
    }
}

void DrinkingSensor::setTimedOut(unsigned int timedOut)
{
    this->timedOut = timedOut;
}

void DrinkingSensor::init(int inputPin)
{
    this->inputPin = inputPin;

    prevTime = millis();
    pinMode(inputPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(inputPin), count, RISING); // interrupt setup

    eeprom.begin(); // EEPROM begin
}

void DrinkingSensor::zero()
{
    velocity = 0;
    volume = 0;
    maxVelocity = 0;
    averageVelocity = 0;
    counter = 1;
}

void DrinkingSensor::saveCycle()
{
    eeprom.get(eepromCycle);  // computing lej cycle and save it into EEPROM
    eepromCycle += volume - lastCycle;
    lastCycle = volume;
    eeprom.put(eepromCycle);
}

float DrinkingSensor::getVelocity()
{
    if(millis() - prevTime > timedOut) velocity = 0;
    return velocity;
}

float DrinkingSensor::getMaxVelocity()
{
    return maxVelocity;
}

float DrinkingSensor::getAverageVelocity()
{
    return averageVelocity / counter;
}

float DrinkingSensor::getVolume()
{
    return volume;
}

float DrinkingSensor::getCycle()
{
    return eepromCycle;
}
