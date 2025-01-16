#include "controller.hpp"

Controller::Controller(){};

//Callback for when a new controller is connected
void Controller::connect(ControllerPtr ctl){
    if(!controller){
        Serial.println("Already Connected to Controller");
        return;
    }
    
    if(!ctl)
        return;

    myController = ctl;
    ControllerProperties properties = ctl->getProperties();
    Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                    properties.product_id);
}

void Controller::disconnect(){
    Serial.println("Disconnecting from controller")
    myController = nullptr;
}

bool Controller::isConnected(){
    if(myController) 
        return myController->isConnected();
    else 
        return false;
}

void Controller::dumpInfo(){
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        myController->index(),        // Controller Index
        myController->dpad(),         // D-pad
        myController->buttons(),      // bitmask of pressed buttons
        myController->axisX(),        // (-511 - 512) left X Axis
        myController->axisY(),        // (-511 - 512) left Y axis
        myController->axisRX(),       // (-511 - 512) right X axis
        myController->axisRY(),       // (-511 - 512) right Y axis
        myController->brake(),        // (0 - 1023): brake button
        myController->throttle(),     // (0 - 1023): throttle (AKA gas) button
        myController->miscButtons(),  // bitmask of pressed "misc" buttons
        myController->gyroX(),        // Gyro X
        myController->gyroY(),        // Gyro Y
        myController->gyroZ(),        // Gyro Z
        myController->accelX(),       // Accelerometer X
        myController->accelY(),       // Accelerometer Y
        myController->accelZ()        // Accelerometer Z
    );
}

Controller::update(){
    buttons[0] = myController->a; //X
    buttons[1] = myController->b; //Circle
    buttons[2] = myController->x; //Square
    buttons[3] = myController->y; //Triangle

    controllerStickPosition[0] = myController->axisX();
    controllerStickPosition[1] = myController->axisY();
    controllerStickPosition[2] = myController->axisRX();
    controllerStickPosition[3] = myController->axisRY();
}

// Arduino setup function. Runs in CPU 1
void setup() {
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    // "forgetBluetoothKeys()" should be called when the user performs
    // a "device factory reset", or similar.
    // Calling "forgetBluetoothKeys" in setup() just as an example.
    // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
    // But it might also fix some connection / re-connection issues.
    BP32.forgetBluetoothKeys();

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
    // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();

    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

    //     vTaskDelay(1);
    delay(150);
}
