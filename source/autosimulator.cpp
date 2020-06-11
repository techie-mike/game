//
// Created by Mikhail Kaskov on 09.06.2020.
//

#include <SFML/System/Clock.hpp>
#include "autosimulator.h"

void AutosimController::getManipulatorData ()
{
    sf::Event event;
    while (main_window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            main_window_->close ();
        }
    }

    getManipulatorDataFromDevice (getKeyboardData);
    testManipulator ();
}

void AutosimController::startProgram () {
    sf::RenderWindow* window = new sf::RenderWindow (sf::VideoMode(800, 600), "SFML works!");
    main_window_ = window;

    mainController ();
//    getManipulatorData ();

}

void AutosimController::testManipulator () {
    printf ("Data from manipulator:\n"
            "AngleWheel %lg\n"
            "Throttle   %lg\n"
            "Brake      %lg\n"
            "Hand_brake %lg\n\n",
            manipulator_data_.angleWheel,
            manipulator_data_.throttle,
            manipulator_data_.brake,
            manipulator_data_.hand_brake);
}

void AutosimController::mainController () {
    sf::Clock clock;
    unsigned __int64 time_cycle_physics = 1000000 / FREQUENCY_PHYSICS;
    unsigned __int64 time_cycle_display = 1000000 / FREQUENCY_DISPLAY;

    while (main_window_->isOpen()) {
        sf::Time time_last_cycle = clock.restart ();

        if (time_last_cycle.asMicroseconds () >= time_cycle_physics) {
            // model

            getManipulatorData ();
        }

        if (time_last_cycle.asMicroseconds () >= time_cycle_display) {
            // display
        }
    }
}

void AutosimController::getManipulatorDataFromDevice (void (* func) (ManipulatorData &)) {
    func (manipulator_data_);
}
