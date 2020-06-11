//
// Created by Mikhail Kaskov on 09.06.2020.
//

#ifndef GAME_AUTOSIMULATOR_H
#define GAME_AUTOSIMULATOR_H

#include <SFML/Graphics.hpp>
#include "inputController.h"
#include <stdio.h>


class AutosimController {
private:
    const int FREQUENCY_PHYSICS = 1000;
    const int FREQUENCY_DISPLAY = 60;


    ManipulatorData   manipulator_data_;
    sf::RenderWindow* main_window_;


    void getManipulatorData ();
    void getManipulatorDataFromDevice (void (*func)(ManipulatorData&));
    void mainController ();

public:
    void startProgram ();

private:
    void testManipulator ();
};


#endif //GAME_AUTOSIMULATOR_H
