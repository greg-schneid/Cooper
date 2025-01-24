#include "robot.hpp"

Robot::Robot(float &angle_, servoType &servo_):
    angle(angle_), 
    servo(servo_),
    leftRear(leftRearPins, pwm),
    rightRear(rightRearPins, pwm),
    leftFront(leftFrontPins, pwm),
    rightFront(rightFrontPins, pwm)
{}

Robot::~Robot(){
}

void Robot::startHardware(){
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

void Robot::update(){
    //Angle Calculation Outlined here:https://www.desmos.com/calculator/qm5yl6s7jk
    updateLegPositions(left_front, servo, angle);
}

void Robot::updateLegPositions(leg legID, servoType servo, float angle){
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
            Serial.printf("Invalid Leg ID %d\n", static_cast<int>(legID));
            break;
    }
}