//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "view.h"

void AutosimView::createWindow (int width, int height) {
    main_window = new sf::RenderWindow (sf::VideoMode(width, height), "Autosimulator 2020");
}

void AutosimView::drawOnWindow (BaseObject** objects, unsigned int active_objects) {
    main_window->clear();


    //----------------------------------------------------------------------------
    additionViewData.window = main_window;
    additionViewData.scale = 100;
    additionViewData.offset_in_window = sf::Vector2f (sf::Vector2f (400, 300));
    additionViewData.camera = camera;
    //----------------------------------------------------------------------------

    setCameraPosition (objects[1]);

    for (size_t i = 0; i < active_objects; i++) {
        if (objects[i] == nullptr) {
            printf ("Error in points on objects!\n");
            exit(1);
        }
//        additionViewData.camera.rotation_angle = 30.f;

        objects[i]->draw (additionViewData);
    }

    main_window->display();
//    main_window->requestFocus();


}

void AutosimView::setCameraPosition (BaseObject* focus_on) {
    camera.position       = focus_on->position;
    camera.rotation_angle = focus_on->rotation_angle;
}
