//
// Created by Mikhail Kaskov on 09.06.2020.
//

#ifndef GAME_AUTOSIMULATOR_H
#define GAME_AUTOSIMULATOR_H

#include <SFML/Graphics.hpp>
//-------------------------------
#include "controller/inputController.h"
#include "models.h"
#include "view.h"
//-------------------------------

#include <stdio.h>


class AutosimController {
private:
    // Number of units of time per second
    // that means then 1sec = 1'000'000 units of time (microseconds)
    const long long NUM_UNITS_IN_ONE_SEC = 1000000;

    const long long FREQUENCY_PHYSICS    = 1000;
    const long long FREQUENCY_DISPLAY    = 60;


    ManipulatorData   manipulator_data_;
    sf::RenderWindow* main_window_;

    AutosimModel autosimModel_;
    AutosimView  autosimView_;


    void getManipulatorData ();
    void getManipulatorDataFromDevice (void (*func)(ManipulatorData&));
    void managerController ();

public:
    void startProgram ();

private:
    void testManipulator ();
};


#endif //GAME_AUTOSIMULATOR_H
