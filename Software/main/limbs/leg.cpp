#include <leg.hpp>

Leg::Leg(uint8_t servo[3], Adafruit_PWMServoDriver &pwmDriver):
    servoPins(servo), pwm(pwmDriver)
{};

void Leg::setServoAngle(servoType servo, uint8_t angle){
    if(servo > 2 || angle > 180)
        //Invalid angle or servo id
        return;
    
    //uint16_t pulse = static_cast<uint16_t>(angle/(180.0)*(SERVOMAX-SERVOMIN));
    uint16_t pulse = SERVOMIN + (angle * (SERVOMAX - SERVOMIN)) / 180;

    
    pwm.setPWM(servoPins[servo], 0, pulse);
}