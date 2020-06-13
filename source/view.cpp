//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "view.h"

void AutosimView::createWindow (int width, int height) {
    main_window = new sf::RenderWindow (sf::VideoMode(width, height), "Autosimulator 2020");
}

void AutosimView::drawOnWindow (BaseObject** objects, unsigned int active_objects) {
    additionViewData.window = main_window;
    additionViewData.scale = 100;
    additionViewData.position_in_window = sf::Vector2f (sf::Vector2f (400, 300));

    setCameraPosition (objects[0]);

    for (size_t i = 0; i < active_objects; i++) {
        objects[i]->draw (additionViewData);
    }
    main_window->display();

}

void AutosimView::setCameraPosition (BaseObject* focus_on) {
    camera.position       = focus_on->position;
    camera.rotation_angle = focus_on->rotation_angle;
}
