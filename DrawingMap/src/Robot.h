#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <raylib.h>
#include "variable"

class Robot{
    Vector2 coordinates = {screenWidth / 2, screenHeight / 2};
    

    Vector2 robotSize = {200, 200};
    float degree = 0;
}

#endif