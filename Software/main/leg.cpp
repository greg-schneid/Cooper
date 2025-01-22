#include "leg.hpp"

Leg::Leg(const uint8_t servo[3], Adafruit_PWMServoDriver &pwmDriver):
    servoPins{servo[0], servo[1], servo[2]},
    pwm(pwmDriver)
{};

void Leg::setServoAngle(servoType servo, float angle){
    if(angle > 180){
      Serial.println("Invalid Angle");
        //Invalid angle or servo id
        return;
    }
        
    //uint16_t pulse = static_cast<uint16_t>(angle/(180.0)*(SERVOMAX-SERVOMIN));
    float pulse = SERVOMIN + (angle * (SERVOMAX - SERVOMIN)/180.0);
    Serial.printf("Sending Pulse of Length %.2f to Servo for angle %.2f\n", pulse, angle);
    pwm.setPWM(servoPins[servo], 0, pulse);
}