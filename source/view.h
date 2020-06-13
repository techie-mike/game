//
// Created by Mikhail Kaskov on 12.06.2020.
//

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>
#include "objects.h"

struct AutosimView {
    void createWindow (int width, int height);
    void drawOnWindow (BaseObject** objects, unsigned int active_objects);
//    void textureLoading ();

    AdditionViewData additionViewData;
    sf::RenderWindow* main_window;

    struct {
        sf::Vector2f position;
        float rotation_angle;
    } camera;

    void setCameraPosition (BaseObject* focus_on);

};
#endif //GAME_VIEW_H
