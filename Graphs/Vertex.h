#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include <iostream>
#include <cstdint>

typedef uint64_t gr_int;

class Vertex
{
private:
    bool isWall = 0;

public:
    float x, y;

    std::vector<gr_int> neighbours;

    Vertex();
    Vertex(float x, float y);
    ~Vertex();

    void append_neighbours(std::vector<gr_int> dest);

    bool IsWall();
};

#endif