#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Define SDA and SCL pins (customizable)
#define SDA_PIN 21 // Default SDA pin for ESP32
#define SCL_PIN 22 // Default SCL pin for ESP32

// Create an instance of the TwoWire class
TwoWire I2Cbus = TwoWire(0); // Use bus number 0

// Create the PWM driver object, specifying the I2C address and bus
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, I2Cbus);

// Define minimum and maximum pulse lengths
#define SERVOMIN  150 // Minimum pulse length count (out of 4096)
#define SERVOMAX  600 // Maximum pulse length count (out of 4096)

void setup() {
  Serial.begin(115200);
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

// Function to map angle (0-180 degrees) to pulse length
int angleToPulse(int angle) {
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

void loop() {
  int servoChannel = 15; // Channel number where the servo is connected (0-15)

  // Sweep servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 10) {
    int pulse = angleToPulse(angle);
    pwm.setPWM(servoChannel, 0, pulse);
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("° | Pulse: ");
    Serial.println(pulse);
    delay(500); // Wait for half a second
  }

  // Sweep servo from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 10) {
    int pulse = angleToPulse(angle);
    pwm.setPWM(servoChannel, 0, pulse);
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("° | Pulse: ");
    Serial.println(pulse);
    delay(500); // Wait for half a second
  }
}
