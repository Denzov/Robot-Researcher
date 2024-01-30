#include "block.hpp"
#include <vector>
#include <cmath>

void Block::setX(double angle, double distance, Vector2 currentPos){
    position.x = cos(angle * PI / 180) * distance + currentPos.x;
}

void Block::setY(double angle, double distance, Vector2 currentPos){
    position.y = sin(angle * PI / 180) * distance + currentPos.y;    
}
