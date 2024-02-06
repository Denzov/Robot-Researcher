#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include <iostream>

typedef uint64_t gr_int;

class Vertex
{
private:
    bool isWall = 0;
    gr_int x, y;    
    
public:
    std::vector<gr_int> neighbours;

    Vertex();
    Vertex(gr_int x, gr_int y);
    ~Vertex();

    void append_neighbours(std::vector<gr_int> dest);

    bool IsWall();
};

#endif