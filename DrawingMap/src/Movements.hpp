#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <raylib.h>
#include <string>

void movementRobot(Vector2 &coord, float &degree);

void movementCamera(Vector2 &coord);

void rotateAndZoom(Camera2D &cam);

void rotateAndZoom(Camera2D &cam);

void screenShotMap(std::string file);

#endif
