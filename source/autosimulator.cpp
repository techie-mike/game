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
    autosimModel_.createDefaultObjects ();
    autosimView_.createWindow (800, 600);

    autosimView_.drawOnWindow (autosimModel_.objects, autosimModel_.numActiveObjects);

//    sf::RenderWindow* window = new sf::RenderWindow (sf::VideoMode(800, 600), "SFML works!");
    main_window_ = autosimView_.main_window;

//    sf::Texture background;
//    background.loadFromFile("map.png");
//    sf::Sprite rectangle;
//    rectangle.scale (sf::Vector2f(8000.f, 4000.f));
//    rectangle.setTexture (background);
//    window->draw(rectangle);
//    window->display();
//    getManipulatorData ();

    managerController ();

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

void AutosimController::managerController () {
    sf::Clock clock;

    unsigned __int64 time_cycle_physics = NUM_UNITS_IN_ONE_SEC / FREQUENCY_PHYSICS;
    unsigned __int64 time_cycle_display = NUM_UNITS_IN_ONE_SEC / FREQUENCY_DISPLAY;

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
