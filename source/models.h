//
// Created by Mikhail Kaskov on 12.06.2020.
//

#ifndef GAME_MODELS_H
#define GAME_MODELS_H

#include "objects.h"
#include <vector>

struct AutosimModel {
    void createDefaultObjects ();

    BaseObject* objects[10];    // temporary
    unsigned int numActiveObjects = 1;
    BaseObject* main_car;

    void createDefaultSettingsForCar (Car* car);
    void loadDefaultTextureInCar     (Car* car);

    void createDefaultMap ();

    void calculationNewPositions (unsigned long long different_time, ManipulatorData &last_manipulator_data);


};

#endif //GAME_MODELS_H
