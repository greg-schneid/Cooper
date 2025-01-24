#ifndef LEG_H
#define LEG_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <cstdint>
#include <stdint.h>
#include <Arduino.h>

#include "constants.hpp"

//Specs for leg: https://www.gxservo.com/en/pd.jsp?id=16

// Define minimum and maximum pulse lengths
#define SERVOMIN 150 // Minimum pulse length count (out of 4096)
#define SERVOMAX  600 // Maximum pulse length count (out of 4096)

class Leg{
    public: 
        Leg(const uint8_t servo[3], Adafruit_PWMServoDriver &pwmDriver);
        void setServoAngle(servoType servo, float angle);
        
    private:
        const uint8_t servoPins[3];
        Adafruit_PWMServoDriver &pwm;
};

#endif