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
    unsigned int numActiveObjects;

    void createDefaultSettingsForCar (Car* car);
    void loadDefaultTextureInCar (Car* car);

    float getCoeffOfRollingFrictionOnArea();
    float getCoeffOfSlidingFrictionForceOnArea();
};

#endif //GAME_MODELS_H
