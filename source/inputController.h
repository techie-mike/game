//
// Created by Mikhail Kaskov on 11.06.2020.
//

#ifndef GAME_INPUTCONTROLLER_H
#define GAME_INPUTCONTROLLER_H

struct ManipulatorData {
    float angleWheel;
    float throttle;
    float brake;
    float hand_brake;
};


// FUNCTIONS FOR READING DATA //
//=============================
void getKeyboardData (ManipulatorData& data);
//=============================

#endif //GAME_INPUTCONTROLLER_H
