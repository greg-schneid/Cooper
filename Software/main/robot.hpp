#ifndef ROBOT_H
#define ROBOT_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#include <cstdint>

#include "limbs/leg.hpp"
#include "enums.hpp"

static const uint8_t leftRearPins[3]  = {0, 1, 2};
static const uint8_t rightRearPins[3] = {3, 4, 5};
static const uint8_t leftFrontPins[3] = {6, 7, 8};
static const uint8_t rightFrontPins[3] = {9, 10, 11};

class Robot{
    public:
        Robot(short (&stickPositions)[4], bool (&buttons)[4]);
        void updateLegPositions(leg legID, servoType servo, uint8_t angle);

    private:
        Leg leftRear; //ID: 0
        Leg rightRear; //ID: 1
        Leg leftFront; //ID: 2
        Leg rightFront; //ID: 3
        
        short* direction;
        bool* controllerButtons;

        TwoWire I2Cbus = TwoWire(0);
        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, I2Cbus);
}

#endif