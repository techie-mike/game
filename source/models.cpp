//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "models.h"

float Car::getPower () {
    return MAX_POWER_ENGINE;
}

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
