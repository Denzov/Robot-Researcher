#ifndef VALUES_H
#define VALUES_H

#include <vector>
#include <raylib.h>
#include "Graph.h"

const int screenWidth = 1920;
const int screenHeight = 1040;

//robot
Vector2 coordinates = {screenWidth / 2, screenHeight / 2};
Vector2 robotSize = {50, 50};

Vector2 blockSize = {5, 5};

//input
float dist = 100;
float angle = 0;
int last_time = 0;
int current_time = 0;


std::string file_name = "map.png";

//graph
Graph graph;
Vector2 vertexSize = {10, 10};
int vertexQuantity = 300000;

//camera
Camera2D camera = {0};
Vector2 cameraCoord = {0, 0};

#endif