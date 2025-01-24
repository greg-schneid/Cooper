#ifndef CONSTANTS_H

#define CONSTANTS_H

#define SDA_PIN 21 // Default SDA pin for ESP32
#define SCL_PIN 22 // Default SCL pin for ESP32

enum leg{
    left_rear = 0,
    right_rear = 1,
    left_front = 2,
    right_front = 3
};

enum servoType{
    abductor = 0,
    upper_leg = 1,
    lower_leg = 2
};

#endif //CONSTANTS_H