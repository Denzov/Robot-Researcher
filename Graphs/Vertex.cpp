#include "Vertex.h"

Vertex::Vertex(){
}

Vertex::Vertex(float x, float y){
    this->x = x;
    this->y = y;
}

Vertex::~Vertex(){
}

bool Vertex::IsWall(){
    return isWall;
}

void Vertex::append_neighbours(std::vector<gr_int> dest){
    for (gr_int i = 0; i < dest.size(); i++)
    {
        neighbours.push_back(dest[i]);
    }
}