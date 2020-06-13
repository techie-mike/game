//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "objects.h"

#include <cmath>
#include "cmath"

//float Car::getPower () {
//    return MAX_POWER_ENGINE;
//}

void Car::powerDistributionOnWheels () {
    char num_pulling_wheels = 0;

    for (int i = 0; i < 4; i++) {
        if (wheel[i].is_pulling)
            num_pulling_wheels++;
    }

    float power_on_one_wheel = power_engine_now / static_cast<float> (num_pulling_wheels);

    for (int i = 0; i < 4; i++) {
        if (wheel[i].is_pulling)
            wheel[i].point->power_now = wheel[i].is_pulling ? power_on_one_wheel : 0;
    }
}


Car::Car ():
    power_engine_now (0),
    drag_coefficient (0)
{
    for (auto &i : wheel) {
        i.point = new Wheel;
        i.is_pulling = false;
        i.point->parent = this;
    }
}

Car::~Car () {
    for (auto &i: wheel) {
        delete i.point;
    }
}

void Car::draw (const AdditionViewData &additionData) {
    for (auto & i : wheel) {
        i.point->draw (additionData);
    }

    sf::Vector2f now_position = (position - additionData.camera.position) * additionData.scale
            + additionData.offset_in_window;

    sf::Vector2f now_size = size_object * additionData.scale;
//    sprite.setSize (sf::Vector2f (100.f, 200.f));

    sprite.setSize (now_size);
    sprite.setOrigin (now_size / 2.f);
    sprite.setPosition (now_position);
    sprite.setRotation (rotation_angle);

    sprite.setPosition (now_position);
    additionData.window->draw (sprite);
}

void Wheel::draw (const AdditionViewData &additionData) {
    sf::Vector2f now_position = (parent->position + position) * additionData.scale + additionData.offset_in_window;
    sf::Vector2f now_size = size_object * additionData.scale;
    sf::Vector2f centre_of_car = (position) * additionData.scale;

//    sf::Vector2f now_position = (parent->position + position) * 100.f;

    float radian_rotation_angle = (parent->rotation_angle * 3.1415f) / 180.f;
    sf::Vector2f new_position{};
    new_position.x = centre_of_car.x * std::cos (radian_rotation_angle)
                   - centre_of_car.y * std::sin (radian_rotation_angle);

    new_position.y = centre_of_car.x * std::sin (radian_rotation_angle)
                   + centre_of_car.y * std::cos (radian_rotation_angle);

    new_position += now_position - centre_of_car;
    sprite.setSize (now_size);
    sprite.setOrigin (now_size / 2.f);

    sprite.setPosition (new_position);

//    additionData.window->draw (sprite);

/*
    //-------------------------------------------------
    //      Centre of car
    sf::CircleShape shape(10);
    shape.setOrigin (sf::Vector2f(10,10));
//
//// set the shape color to green
    shape.setFillColor(sf::Color(250, 0, 0));
    shape.setPosition (now_position - centre_of_car);
    additionData.window->draw (shape);
    //-------------------------------------------------
    */
    // Then we will be rotate wheel

    sprite.setRotation (parent->rotation_angle + rotation_angle);

//    sprite.setRotation (45.f);
    additionData.window->draw (sprite);
}

void Car::calculationNewState () {

}

void Wheel::calculationNewState () {

}
