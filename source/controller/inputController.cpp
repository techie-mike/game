//
// Created by Mikhail Kaskov on 11.06.2020.
//

#include "inputController.h"
#include <SFML/Window/Keyboard.hpp>


void getKeyboardData (ManipulatorData& data) {
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::W)) {
        data.throttle = 1.0;
    } else
        data.throttle = 0.0f;

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::S)) {
        data.brake = 1.0f;
    } else
        data.brake = 0.0f;

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space))
        data.hand_brake = 1.0f;
    else
        data.hand_brake = 0.0f;

    //-------------temporarily---------------
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::A)) {
        data.angleWheel = -1.0f;
    }
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::D))
        data.angleWheel = 1.0f;
    else
        data.angleWheel = 0.0f;
}