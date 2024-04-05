#include "Vertex.h"

Vertex::Vertex(){
}

Vertex::Vertex(Vector2 position, bool wallIs){
    pos.x = position.x;
    pos.y = position.y;
    isWall = wallIs;
}

Vertex::~Vertex(){
}


void Vertex::append_neighbours(std::vector<Vector2> neighs){
    for (int i = 0; i < neighs.size(); i++)
    {
        neighbours.push_back(neighs[i]);
    }
}