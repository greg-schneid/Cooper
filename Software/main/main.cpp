// Include the Arduino header file for core functionality
#include <Arduino.h>
#include <Bluepad32.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <cstdint>

#include "controller.hpp"
#include "robot.hpp"

// Declare any global variables here
Controller controller;
Robot robot(&controller.controllerStickPositions, &controller.buttons);

const bool DUMP_CONTROLLER_INFO = false;

// Function prototypes (optional but good practice)
void setupBluetooth();
void setupServoDriver();

void setup();
void loop();

// The setup function runs once when the device is powered on or reset
void setup() {
    Serial.begin(115200);
    setupBluetooth();
    setupServoDriver();
}

// The loop function runs continuously after setup
void loop() {
    //Getting New Data from bluetooth controller
    bool dataUpdated = BP32.update();
    if(dataUpdated)
        controller.update();
    delay(150);
}

void setupBluetooth(){
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    //Setup the Bluepad32 callbacks
    BP32.setup([&controller](){controller.connect()}, [&controller](){controller.disconnect()});

    //Forget bluetooth keys should be called when a factory reset is done, doing it on setup works
    BP32.forgetBluetoothKeys();

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}

void setupServoDriver(){
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