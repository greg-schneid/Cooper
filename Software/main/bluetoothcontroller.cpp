#include "bluetoothcontroller.hpp"

BluetoothController::BluetoothController(){};

//Callback for when a new controller is connected
void BluetoothController::connect(ControllerPtr ctl){
    Serial.println("Calling Connect function");
    if(myController){
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

void BluetoothController::disconnect(ControllerPtr ctl){
    Serial.println("Disconnecting from controller");
    
    if(!ctl) 
        return;

    myController = nullptr;
}

bool BluetoothController::isConnected(){
    if(myController) 
        return myController->isConnected();
    else 
        return false;
}

void BluetoothController::dumpInfo(){
    Serial.printf(
    "Buttons: X=%d, Circle=%d, Square=%d, Triangle=%d | Stick Positions: AxisX=%d, AxisY=%d, AxisRX=%d, AxisRY=%d\n",
    buttons[0], buttons[1], buttons[2], buttons[3], 
    controllerStickPositions[0], controllerStickPositions[1], 
    controllerStickPositions[2], controllerStickPositions[3]
    );
}

void BluetoothController::update(){
    if (!myController || !myController->isConnected()) {
        return;
    }
    buttons[0] = myController->a(); //X
    buttons[1] = myController->b(); //Circle
    buttons[2] = myController->x(); //Square
    buttons[3] = myController->y(); //Triangle

    controllerStickPositions[0] = myController->axisX();
    controllerStickPositions[1] = myController->axisY();
    controllerStickPositions[2] = myController->axisRX();
    controllerStickPositions[3] = myController->axisRY();

    dumpInfo();
}
