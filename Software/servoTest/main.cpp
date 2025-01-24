// Include the Arduino header file for core functionality
#include <Arduino.h>
#include <Wire.h>

#include <cstdint>
#include <stdint.h>

#include "robot.hpp"
#include "constants.hpp"

float angle = 0;
servoType servo = abductor;

// Declare any global variables here
Robot robot(angle, servo);

bool updateServoType(const String &input);

// The setup function runs once when the device is powered on or reset
void setup() {
    Serial.begin(115200);
    Serial.println("Starting boot sequence");
    robot.startHardware();
    Serial.println("Succesfully Started Hardware");
}

// The loop function runs continuously after setup
void loop() {
    if(Serial.available() > 0){
        String input = Serial.readStringUntil('\n');
        
        //Data Validation
        if (input.toInt() != 0 || input == "0") {
            angle = input.toInt();
            Serial.printf("Angle stored: %d\n", angle);
            robot.update();
        } else {
            updateServoType(input);
        }
    }
        
    delay(150);
}

bool updateServoType(const String &input){
    if(input == "abductor"){
        servo = abductor;
        return true;
    }
    else if(input == "upper_leg"){
        servo = upper_leg;
        return true;
    }
    else if(input == "lower_leg"){
        servo = lower_leg;
        return true;
    }
    else{
        Serial.println("Invalid Input");
        return false;
    }
}