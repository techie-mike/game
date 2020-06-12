//
// Created by Mikhail Kaskov on 12.06.2020.
//

#ifndef GAME_MODELS_H
#define GAME_MODELS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "controller/manipulatorData.h"

struct BaseObject
{
    sf::Vector2f world_position;    // unit: metres
    sf::Vector2f size_object;       // unit: meters

    // Positive clockwise direction
    float world_rotation_angle;     // unit: degrees

    sf::Texture texture;
    sf::Sprite  sprite;

    virtual void draw() = 0;
    virtual void calculationNewState() = 0;
};

struct BaseMovingObject :
        public BaseObject
{
    // Positive clockwise direction
    float angular_moment; // unit: Newton*metres/seconds
    float moment_power;   // unit: Newton*metres

    sf::Vector2f speed;   // unit: metres/seconds
    sf::Vector2f force;   // unit: Newton
};

struct Wheel :
        public BaseMovingObject
{
    BaseMovingObject* body_auto;
    float wheel_diameter;   // unit: metres
    float rotation_speed;   // unit: rad/sec
                            // forward - positive, back - negative

    float power_now;   // unit: Newton * meters / second

//    float getPowerOnWheel();

    virtual void draw();
    virtual void calculationNewState();
private:
    float getCoeffOfRollingFrictionOnArea();
    float getCoeffOfSlidingFrictionForceOnArea();
};

struct Car :
    public BaseMovingObject
{
    const float MAX_POWER_ENGINE = 100 * 735.5f;    // unit: H*m

    float getPower();   // unit: H*m/c
    float power_engine_now;

    float drag_coefficient;

    ManipulatorData state_manipulator;
    void powerDistributionOnWheels();

//===================================
//  Front left  wheel - 0   item
//  Front right wheel - 1st item
//  Back  right wheel - 2nd item
//  Back  left  wheel - 3rd item
//      [0]--+--[1]
//           |
//           |
//      [3]--+--[2]
//===================================
        struct {
        Wheel* point;
        bool is_pulling;
    } wheel[4];

    virtual void draw();
    virtual void calculationNewState();
};
#endif //GAME_MODELS_H
