#ifndef LEG_H
#define LEG_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <cstdint>
#include <stdint.h>
#include <Arduino.h>

#include "constants.hpp"

// Define minimum and maximum pulse lengths
#define SERVOMIN 500 // Minimum pulse length in microseconds)
#define SERVOMAX  4096 // Maximum pulse length in microseconds)
const float pulse_width_per_degree = SERVOMIN + (SERVOMAX - SERVOMIN)/180;

class Leg{
    public: 
        Leg(const uint8_t servo[3], Adafruit_PWMServoDriver &pwmDriver);
        void setServoAngle(servoType servo, float angle);
        
    private:
        const uint8_t servoPins[3];
        Adafruit_PWMServoDriver &pwm;
};

#endif