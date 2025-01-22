#include "leg.hpp"

Leg::Leg(const uint8_t servo[3], Adafruit_PWMServoDriver &pwmDriver):
    servoPins{servo[0], servo[1], servo[2]},
    pwm(pwmDriver)
{};

void Leg::setServoAngle(servoType servo, float angle){
    Serial.printf("In Leg. Attempting to send signal to pin: %u. Angle: %.2f\n", servoPins[servo], angle);
    if(angle > 180){
      Serial.println("Invalid Angle");
        //Invalid angle or servo id
        return;
    }
        
    //uint16_t pulse = static_cast<uint16_t>(angle/(180.0)*(SERVOMAX-SERVOMIN));
    Serial.println("Calculating Pulse");
    float pulse = SERVOMIN + (angle * (SERVOMAX - SERVOMIN)/180.0);
    Serial.printf("Sending Pulse of Length %.2f to Servo %\n", pulse, servoPins[servo]);
    pwm.setPWM(servoPins[servo], 0, pulse);
    Serial.println("Successfully sent Signal");
}