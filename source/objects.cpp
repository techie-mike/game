//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "objects.h"

#include <cmath>
#include "cmath"

//float Car::getPower () {
//    return MAX_POWER_ENGINE;
//}

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

//    printf ("Position camera: %f\n"
//            "Position car:    %f\n\n", additionData.camera.position.y, position.y);

    sf::Vector2f now_position = (position - additionData.camera.position) * additionData.scale
            + additionData.offset_in_window;

//    printf ("Now position: %f\n\n", now_position.y);
    sf::Vector2f now_size = size_object * additionData.scale;
//    sprite.setSize (sf::Vector2f (100.f, 200.f));

    sprite.setSize (now_size);
    sprite.setOrigin (now_size / 2.f);
    sprite.setPosition (now_position);
    sprite.setRotation (rotation_angle - additionData.camera.rotation_angle);

//    sprite.setPosition (now_position);
    additionData.window->draw (sprite);
}

void Wheel::draw (const AdditionViewData &additionData) {
    sf::Vector2f now_position = (parent->position + position - additionData.camera.position) * additionData.scale + additionData.offset_in_window;
    sf::Vector2f now_size = size_object * additionData.scale;
    sf::Vector2f centre_of_car = (position) * additionData.scale;

//    sf::Vector2f now_position = (parent->position + position) * 100.f;

    float radian_rotation_angle = ((parent->rotation_angle - additionData.camera.rotation_angle) * 3.1415f) / 180.f;
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

    sprite.setRotation (parent->rotation_angle + rotation_angle - additionData.camera.rotation_angle);

//    sprite.setRotation (45.f);
    additionData.window->draw (sprite);
}

void Car::calculationNewState (float last_cycle_time, ManipulatorData &last_input_data) {
    state_manipulator = last_input_data;

    turnWheel ();
    getPowerEngine ();
    powerDistributionOnWheels ();
    calculationOfForcesOnWheels ();
    calculationOfForcesOnCar ();

//==============================================MAIN=PART==============================================
    position.x -= speed.x * last_cycle_time + force.x / mass_of_car * last_cycle_time * last_cycle_time / 2.f;
    speed.x += force.x / mass_of_car * last_cycle_time;

    position.y -= speed.y * last_cycle_time + force.y / mass_of_car * last_cycle_time * last_cycle_time / 2.f;
    speed.y += force.y / mass_of_car * last_cycle_time;

    rotation_angle -= angular_moment * last_cycle_time +  moment_power / 10000.f * last_cycle_time * last_cycle_time / 2.f;
    printf ("Rotation_angle: %f\n\n", rotation_angle);
//    rotation_angle += 0.1f;

}

void Wheel::calculationNewState (float last_cycle_time, ManipulatorData &last_input_data) {

}

void BaseObject::draw (const AdditionViewData &additionData) {
    sf::Vector2f now_position = (position + additionData.camera.position) * additionData.scale
            + additionData.offset_in_window;
    sf::Vector2f now_size = size_object * additionData.scale /*/ 100.f*/;

    sprite.setOrigin (additionData.camera.position + size_object / 2.f);
    sprite.setSize (now_size);
    sprite.setRotation (additionData.camera.rotation_angle);

    printf ("++++++++++++++++++++++\n\n");
    additionData.window->draw (sprite);
}

void BaseObject::calculationNewState (float last_cycle_time, ManipulatorData &last_input_data) {

}

//==========================================CAR=FUNCTIONS==========================================
void Car::getPowerEngine () {
    power_engine_now = MAX_POWER_ENGINE * state_manipulator.throttle;
}

void Car::powerDistributionOnWheels () {
    char num_pulling_wheels = 0;

    for (auto & i : wheel) {
        if (i.is_pulling)
            num_pulling_wheels++;
    }

    float power_on_one_wheel = power_engine_now / static_cast<float> (num_pulling_wheels);

    for (auto & i : wheel) {
//        if (i.is_pulling)
            i.point->power_now = i.is_pulling ? power_on_one_wheel : 0;
    }
}

void Car::turnWheel () {
    float angle_of_rotation = state_manipulator.angleWheel * MAX_ANGLE;
    for (auto &i : wheel) {
        if (i.is_rotating_wheel)
            i.point->rotation_angle = static_cast<float> (i.is_rotating_wheel) * angle_of_rotation;
        else
            i.point->rotation_angle = 0;
    }
}

void Car::calculationOfForcesOnWheels () {
    for (auto &i : wheel) {
        i.point->calculationOfForceOnOneWheel ();
    }
}

void Car::calculationOfForcesOnCar () {
    force = sf::Vector2f (0,0);
    moment_power = 0;

    for (auto &i : wheel) {
        float angle_of_rotation = i.point->rotation_angle * 3.1415f / 180.f;
        force.y += std::cos (angle_of_rotation) * i.point->force.y;
        force.x += std::sin (angle_of_rotation) * i.point->force.y;
        moment_power +=  10.f* std::sin (angle_of_rotation) * i.point->force.y /*/ std::abs (i.point->position.y)*/;
//        printf ("Sin %f\n\n", std::sin (angle_of_rotation));
//        printf ("Force.y %f\n\n", i.point->force.y);
//        printf ("Moment_power: %f\n\n", moment_power);
    }
}

//==========================================WHEEL=FUNCTIONS==========================================

void Wheel::calculationOfForceOnOneWheel () {

    if (std::abs (speed.y) < 1.f)
        force.y = power_now * 10;
    else
        force.y = power_now / speed.y;

    if (std::abs (parent->speed.y) > 1e-10f) {
        force.y -= dynamic_cast<Car*>(parent)->mass_of_car * 9.8f * 0.02f;
    }
    printf ("Speed: %f\n", parent->speed.y);
}

