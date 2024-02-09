#ifndef VALUES_H
#define VALUES_H

#include <vector>
#include <raylib.h>
#include <Graph.h>

const int screenWidth = 1920;
const int screenHeight = 1040;

//robot
Vector2 coordinates = {screenWidth / 2, screenHeight / 2};
Vector2 robotSize = {50, 50};

//input
float dist = 0;
float angle = 0;

std::string file_name = "map.png";

//graph
Graph graph(0);

//camera
Camera2D camera = {0};
Vector2 cameraCoord = {0, 0};

#endif