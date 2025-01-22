// Include the Arduino header file for core functionality
#include <Arduino.h>
#include <Bluepad32.h>
#include <Wire.h>

#include <cstdint>
#include <stdint.h>

#include "bluetoothcontroller.hpp"
#include "robot.hpp"
#include "constants.hpp"

// Declare any global variables here
BluetoothController controller;
Robot robot(controller.controllerStickPositions, controller.buttons);

const bool DUMP_CONTROLLER_INFO = false;

// Function prototypes (optional but good practice)
void setupBluetooth();

// The setup function runs once when the device is powered on or reset
void setup() {
    //Serial.begin(115200);
    Serial.begin(9600);
    Serial.println("Starting boot sequence");
    setupBluetooth();
    Serial.println("Finished Setting up bluetooth. Starting Hardware");
    robot.startHardware();
    Serial.println("Succesfully Started Hardware");
}

// The loop function runs continuously after setup
void loop() {
    //Getting New Data from bluetooth controller
    bool dataUpdated = BP32.update();
    if(dataUpdated){
        controller.update();
        robot.update();
    }
        
    delay(150);
}

void setupBluetooth(){
    Serial.println("Setting Up Bluetooth");
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    //Setup the Bluepad32 callbacks
    BP32.setup([](ControllerPtr ctl){controller.connect(ctl);}, [](ControllerPtr ctl){controller.disconnect(ctl);});

    //Forget bluetooth keys should be called when a factory reset is done, doing it on setup works
    BP32.forgetBluetoothKeys();

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}