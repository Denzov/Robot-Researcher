#ifndef VALUES_H
#define VALUES_H

#include <vector>
#include <raylib.h>
#include "block.hpp"

const int screenWidth = 1920;
const int screenHeight = 1040;

//robot
Vector2 coordinates = {screenWidth / 2, screenHeight / 2};
Vector2 robotSize = {50, 50};

//output
float dist = 0;
float angle = 0;

std::vector<Block> walls;
std::string file_name = "map.png";

int game_time = 0;
int previous_time =  0;

//camera
Camera2D camera = {0};
Vector2 cameraCoord = {0, 0};

#endif