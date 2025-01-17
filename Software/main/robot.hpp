#ifndef ROBOT_H
#define ROBOT_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#include <cstdint>
#include <stdint.h>
#include <math.h>

#include "leg.hpp"
#include "constants.hpp"

const uint8_t leftRearPins[3]  = {0, 1, 2};
const uint8_t rightRearPins[3] = {3, 4, 5};
const uint8_t leftFrontPins[3] = {6, 7, 8};
const uint8_t rightFrontPins[3] = {9, 10, 11};

class Robot{
    public:
        Robot(short (&stickPositions)[4], bool (&buttons)[4]);
        ~Robot();
        void update();
        void startHardware();

    private:
        void updateLegPositions(leg legID, servoType servo, uint8_t angle);

        Leg leftRear; //ID: 0
        Leg rightRear; //ID: 1
        Leg leftFront; //ID: 2
        Leg rightFront; //ID: 3
        
        short* direction;
        bool* controllerButtons;

        TwoWire I2Cbus = TwoWire(0);
        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, I2Cbus);
};

#endif