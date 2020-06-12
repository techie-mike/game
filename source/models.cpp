//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "models.h"
#include "objects.h"


void AutosimModel::createDefaultObjects () {
    Car* main_car = new Car;

    settingsCar settings;
    createDefaultSettingsForCar (main_car);


//    loadDefaultTextureInCar (main_car);
    objects[numActiveObjects] = main_car;
    numActiveObjects++;
}

void AutosimModel::loadDefaultTextureInCar (Car* car) {
    car->texture.loadFromFile ("car.png");
    car->sprite.scale      (sf::Vector2f(4.2, 1.6));
    car->sprite.setOrigin  (car->size_object / 2.0f);
    car->sprite.setTexture (car->texture);

    for (auto &i : car->wheel) {
        i.point->size_object = sf::Vector2f();

        i.point->wheel_diameter = 0.63;
        i.point->sprite.scale     (sf::Vector2f(0.24, 0.63));
        i.point->sprite.setOrigin (i.point->size_object / 2.0f);

        i.point->texture.loadFromFile ("tire.png");
        i.point->sprite.setTexture (i.point->texture);
    }
}

void AutosimModel::createDefaultSettingsForCar (Car* car) {
    car->size_object      = sf::Vector2f (1.6, 4.2);
    car->weight_all_car   = 1500.0;
    car->drag_coefficient = 0.15;

    car->wheel[0].is_rotating_wheel = 1;
    car->wheel[1].is_rotating_wheel = 1;
    car->wheel[2].is_rotating_wheel = 0;
    car->wheel[3].is_rotating_wheel = 0;

    car->wheel[0].is_pulling = false;
    car->wheel[1].is_pulling = false;
    car->wheel[2].is_pulling = true;
    car->wheel[3].is_pulling = true;

    loadDefaultTextureInCar (car);

//    car.name_file_texture_car   = "car.png";
//    car.name_file_texture_wheel = "tire.png";
}
