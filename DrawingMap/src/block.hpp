#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>

class Block{
public:
    Vector2 position;
    Vector2 size = {10, 10};
    Color color = BLACK;

    void setX(double angle, double distance, Vector2 currentPos);
    void setY(double angle, double distance, Vector2 currentPos); 
};

#endif