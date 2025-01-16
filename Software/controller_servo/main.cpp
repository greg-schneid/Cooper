// Include the Arduino header file for core functionality
#include <Arduino.h>
#inlcude <Bluepad32.h>
#include <cstdint>

#include "controller.hpp"

// Declare any global variables here
Controller controller;
const bool DUMP_CONTROLLER_INFO = false;


// Function prototypes (optional but good practice)
void setupBluetooth();

void setup();
void loop();


// The setup function runs once when the device is powered on or reset
void setup() {
    Serial.begin(115200);
    setupBluetooth();
    
}

// The loop function runs continuously after setup
void loop() {
    //Getting New Data from bluetooth controller
    bool dataUpdated = BP32.update();
    if(dataUpdated)
        controller.update();
    
    if(DUMP_CONTROLLER_INFO)
        controller.dumpInfo();

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
