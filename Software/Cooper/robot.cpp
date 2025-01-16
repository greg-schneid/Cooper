#include "robot.hpp"

Robot::Robot(short (&stickPositions)[4], bool (&buttons)[4])
    : direction(stickPositions), 
    controllerButtons(buttons),
    leftRear(leftRearPins, pwm),
    rightRear(rightRearPins, pwm),
    leftFront(leftFrontPins, pwm),
    rightFront(rightFrontPins, pwm)
{
    Serial.println("Initializing PCA9685 Servo Controller...");

    // Initialize I2C communication with custom SDA and SCL pins
    I2Cbus.begin(SDA_PIN, SCL_PIN, 100000); // 100kHz I2C frequency

    // Initialize the PCA9685 using the I2Cbus instance
    pwm.begin();

    // Set the PWM frequency to 50 Hz (standard for servos)
    pwm.setPWMFreq(50);

    // Small delay to allow settings to take effect
    delay(10);
}

Robot::~Robot(){
    direction = nullptr;
    controllerButtons = nullptr;
}

void Robot::update(){
    
    //short* direction;
    //bool* controllerButtons;

    //Angle Calculation Outlined here: https://www.desmos.com/calculator/tbmkiml4pm
    uint8_t angle = 90;

    if(direction[0]!=0){
        angle = static_cast<uint8_t>(round(atan(max(direction[1],static_cast<short>(0))/direction[0]) * (180/PI)));
    }
    updateLegPositions(left_front, abductor, angle);
}

void Robot::updateLegPositions(leg legID, servoType servo, uint8_t angle){
    switch(legID){
        case left_front:
            leftFront.setServoAngle(servo, angle);
            break;
        case left_rear:
            leftRear.setServoAngle(servo, angle);
            break;
        case right_front:
            rightFront.setServoAngle(servo, angle);
            break;
        case right_rear:
            rightRear.setServoAngle(servo, angle);
            break;
        default:
            //Invalid Leg ID
            Serial.println("Invalid Leg ID");
            break;
    }
}