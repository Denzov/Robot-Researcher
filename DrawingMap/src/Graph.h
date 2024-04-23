#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <map>
#include <vector>

#include "Vertex.h"

struct cmpByStringLength
{

    bool operator()(const Vector2 &lhs, const Vector2 &rhs) const
    {
        if (lhs.y < rhs.y)
        {
            return true;
        }
        else if ((int) lhs.y == (int) rhs.y)
        {
            return lhs.x < rhs.x;
        }
        else
        {
            return false;
        }
    }
};

class Graph
{
public:
    std::map<Vector2, Vertex, cmpByStringLength> *graph = new std::map<Vector2, Vertex, cmpByStringLength>;
    std::vector<Vertex> *walls = new std::vector<Vertex>;
    std::map<Vector2, Vertex, cmpByStringLength> *unseen = new std::map<Vector2, Vertex, cmpByStringLength>;

    Graph();
    ~Graph();
    
    std::vector<Vector2> find_path(Vector2 from, Vector2 to);
    void makeSeen(Vector2 posEyes, float angle, Vector2 vertexSize);
    void append_wall(Vector2 ver);
    void append_vert(Vector2 ver, bool wallIs);

    Vector2 countingClosestUnseen(Vector2 posFrom);

};

#endif