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

    controllerStickPositions[0] = myController->axisX();
    controllerStickPositions[1] = myController->axisY();
    controllerStickPositions[2] = myController->axisRX();
    controllerStickPositions[3] = myController->axisRY();

    controller.dumpInfo();
}
