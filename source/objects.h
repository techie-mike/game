//
// Created by Mikhail Kaskov on 12.06.2020.
//

#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

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
    BaseObject* parent;

//    float getPowerOnWheel();

    virtual void draw();
    virtual void calculationNewState();
private:

};

struct Car :
        public BaseMovingObject
{
    const float MAX_POWER_ENGINE = 100 * 735.5f;    // unit: H*m
    const float MAX_ANGLE        = 50.f;

//    float getPower();   // unit: H*m/c
    float power_engine_now;
    float drag_coefficient;

    float weight_all_car{};
    ManipulatorData state_manipulator{};

    void powerDistributionOnWheels();

//===================================
//  Front left  wheel - 0   item
//  Front right wheel - 1st item
//  Back  left  wheel - 2rd item
//  Back  right wheel - 3nd item
//      [0]--+--[1]
//           |
//           |
//      [2]--+--[3]
//===================================
    struct {
        Wheel* point;
        bool is_pulling;
        char is_rotating_wheel;
        // If wheel:
        // can`t rotate             0
        // rotate normal direction -1
        // rotate invert direction  1
        //----------------------------
    } wheel[4]{};

    Car();
   ~Car();

    virtual void draw();
    virtual void calculationNewState();
};

struct settingsCar {
    const char* name_file_texture_car{};
    const char* name_file_texture_wheel{};

    bool wheel_is_pulling[4]{};
    float drag_coefficient{};

    sf::Vector2f size_car;

    struct {
        sf::Vector2f offset_position;
        sf::Vector2f size;
        bool is_pulling[2]{};           // left [0]----[1] right
        char is_rotating_wheel[2]{};    // left [0]----[1] right
    } one_front_wheel;

    struct {
        sf::Vector2f offset_position;
        sf::Vector2f size;
        bool is_pulling[2]{};           // left [0]----[1] right
        char is_rotating_wheel[2]{};    // left [0]----[1] right
    } one_back_wheel;
};

#endif //GAME_OBJECTS_H
