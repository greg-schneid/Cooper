#include "robot.hpp"

Robot::Robot(short (&stickPositions)[4], bool (&buttons)[4])
    : direction(stickPositions), 
    controllerButtons(buttons),
    leftRear(leftRearPins, pwm),
    rightRear(rightRearPins, pwm),
    leftFront(leftFrontPins, pwm),
    rightFront(rightFrontPins, pwm)
{}

Robot::~Robot(){
    direction = nullptr;
    controllerButtons = nullptr;
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
    
    //short* direction;
    //bool* controllerButtons;

    //Angle Calculation Outlined here:https://www.desmos.com/calculator/qm5yl6s7jk
    if(abs(direction[0]) < 20 && abs(direction[1]) < 20){
      Serial.println("Within Deadzone. Not updating leg angles");
      return;
    }
    
    Serial.println("Calculating New Angle");
    float x = static_cast<float>(direction[0]);
    float y = -1* static_cast<float>(direction[1]);
    float angle = 90;
    if(x!=0){
      angle = fabs(atan2(x,fmax(y,0.0))*180/M_PI -90);
    }

    Serial.printf("Updating leg position to: %.2f\n", angle);
    updateLegPositions(left_front, abductor, angle);
}

void Robot::updateLegPositions(leg legID, servoType servo, float angle){
    switch(legID){
        case left_front:
            Serial.printf("Updating Left Front Servo. Servo: %d\n", servo);
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