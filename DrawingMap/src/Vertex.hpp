#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include <iostream>

typedef int gr_int;

class Vertex
{
private:
    bool isWall = 0;
    float x, y;    
    
public:
    std::vector<gr_int> neighbours;
    

    Vertex();
    Vertex(float x, float y);
    ~Vertex();

    void append_neighbours(std::vector<gr_int> dest);

    bool IsWall();
};

#endif