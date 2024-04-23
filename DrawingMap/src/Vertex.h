#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include <iostream>
#include <cstdint>
#include <raylib.h>

typedef uint64_t gr_int;

class Vertex
{
private:

public:
    bool isWall = 0;
    Vector2 pos;

    std::vector<Vector2> neighbours;

    Vertex();
    Vertex(Vector2 position, bool wall);
    ~Vertex();

    void append_neighbours(std::vector<Vector2> neighs);

};

#endif