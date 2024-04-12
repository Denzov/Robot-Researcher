#ifndef _COUNTING_FUNCS_HPP_
#define _COUNTING_FUNCS_HPP_
#include <cmath>
#include <raylib.h>

Vector2 countingCoordinates(float length, float deg, Vector2 coords);

Vector2 roundingToVertSize(Vector2 pos, Vector2 vertexSize);

bool IsPreWallExist(Vector2 posTrueWall, Vector2 lidarPos, Vector2 posWall);

#endif //!_COUNTING_FUNCS_HPP_