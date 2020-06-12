//
// Created by Mikhail Kaskov on 12.06.2020.
//

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>
#include "objects.h"

struct AutosimView {
    void createWindow (int width, int height);
    void drawOnWindow (BaseObject* objects, unsigned int asctive_objects);
//    void textureLoading ();
    sf::RenderWindow* main_window_;

};
#endif //GAME_VIEW_H
