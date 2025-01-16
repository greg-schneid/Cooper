#ifndef LEG_H
#define LEG_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <cstdint>

#include "../enums.hpp"

// Define minimum and maximum pulse lengths
#define SERVOMIN 150 // Minimum pulse length count (out of 4096)
#define SERVOMAX  600 // Maximum pulse length count (out of 4096)

class Leg{
    public: 
        Leg(uint8_t servo[3], Adafruit_PWMServoDriver &pwmDriver);
        void setServoAngle(servoType servo, uint8_t angle);
        
    private:
        uint8_t servoPins[3];
        Adafruit_PWMServoDriver &pwm;
}

#endif