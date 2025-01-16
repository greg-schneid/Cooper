#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <Bluepad32.h>

//Class for Handling Interfacing with controller
class Controller{
    public:
        Controller();
        void connect(ControllerPtr ctl);
        void disconnect();
        void update();
        void dumpInfo();

        bool isConnected();

        //No Getters and Setters to reduce overhead
        short controllerStickPositions[4] = {}; //LS Left Right | LS Up Down | RS Left Right | RS Up Down
        bool buttons[4] = {}; //Main 4 buttons

    private:
        ControllerPtr myController = nullptr; //Verify if this needs to be here
}

#endif