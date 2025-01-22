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
    //Angle Calculation Outlined here:https://www.desmos.com/calculator/qm5yl6s7jk

    //Abductor
    float x = static_cast<float>(direction[0]);
    float y = -1* static_cast<float>(direction[1]);
    float angle = 90;
    if(x!=0){
      angle = fabs(atan2(x,fmax(y,0.0))*180/M_PI -90);
    }
     if(abs(x) < 20 && abs(y) < 20){
      Serial.printf("Within deadzone (Angle: %.2f degrees). Not updating Angle. X-Axis: %.1f | Y-Axis: %.1f\n", angle, x, y);
      return;
    }

    Serial.printf("Angle is %.2f degrees. X-Axis: %.1f | Y-Axis: %.1f\n", angle, x, y);
    updateLegPositions(left_front, abductor, angle);

    //Upper Leg
    float ux = static_cast<float>(direction[2]);
    float uy = -1* static_cast<float>(direction[3]);
    float uangle = 90;
    if(x!=0){
      uangle = fabs(atan2(ux,fmax(uy,0.0))*180/M_PI -90);
    }
     if(abs(ux) < 20 && abs(uy) < 20){
      //Serial.printf("Within deadzone (Angle: %.2f degrees). Not updating Angle. X-Axis: %.1f | Y-Axis: %.1f\n", angle, x, y);
      return;
    }

    //Serial.printf("Angle is %.2f degrees. X-Axis: %.1f | Y-Axis: %.1f\n", angle, x, y);
    updateLegPositions(left_front, upper_leg, uangle);
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