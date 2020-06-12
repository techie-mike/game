//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "view.h"

void AutosimView::createWindow (int width, int height) {
    main_window_ = new sf::RenderWindow (sf::VideoMode(width, height), "Autosimulator 2020");
}

void AutosimView::drawOnWindow (BaseObject* objects, unsigned int asctive_objects) {

}
