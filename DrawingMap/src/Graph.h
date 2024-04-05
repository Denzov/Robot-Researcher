#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <map>

#include "Vertex.h"

struct cmpByStringLength{
    
    bool operator()(const Vector2 &lhs, const Vector2 &rhs) const
    {
        if (lhs.x < rhs.x)
        {
            return true;
        }
        else
        {
            return lhs.y < rhs.y;
        }
    }
};

class Graph
{
public:
    std::map<Vector2, Vertex, cmpByStringLength> *graph = new std::map<Vector2, Vertex, cmpByStringLength>;
    std::map<Vector2, Vertex, cmpByStringLength> *walls = new std::map<Vector2, Vertex, cmpByStringLength>;

    Graph();
    ~Graph();

    void append_wall(Vector2 ver);
    void append_vert(Vector2 ver, bool wallIs);
};

#endif