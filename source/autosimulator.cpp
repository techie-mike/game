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
    autosimModel_.createDefaultMap ();

    autosimView_.createWindow (800, 600);

//    autosimView_.drawOnWindow (autosimModel_.objects, autosimModel_.numActiveObjects);

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

    unsigned __int64 time_last_physics = 0;
    unsigned __int64 time_last_display = 0;

    const unsigned __int64 time_cycle_physics = NUM_UNITS_IN_ONE_SEC / FREQUENCY_PHYSICS;
    const unsigned __int64 time_cycle_display = NUM_UNITS_IN_ONE_SEC / FREQUENCY_DISPLAY;

//    autosimView_.main_window->setVerticalSyncEnabled(false);

    getManipulatorData ();

    while (autosimView_.main_window->isOpen()) {
//        sf::Time time_last_cycle = clock.getElapsedTime();

        if ((clock.getElapsedTime().asMicroseconds () - time_last_physics) >= time_cycle_physics) {
            unsigned long long send_time = clock.getElapsedTime().asMicroseconds () - time_last_physics;
            time_last_physics = clock.getElapsedTime().asMicroseconds ();
            // model
            autosimModel_.calculationNewPositions (send_time, manipulator_data_);
            autosimView_.setCameraPosition (autosimModel_.objects[1]);
            getManipulatorData ();
            // TEMPORARILY //
//            autosimModel_.objects[0].
            //-------------//

        }


        if ((clock.getElapsedTime().asMicroseconds () - time_last_display) >= time_cycle_display) {
            time_last_display = clock.getElapsedTime().asMicroseconds ();
            autosimView_.drawOnWindow (autosimModel_.objects, autosimModel_.numActiveObjects);

        }
    }
}

void AutosimController::getManipulatorDataFromDevice (void (* func) (ManipulatorData &)) {
    func (manipulator_data_);
}
