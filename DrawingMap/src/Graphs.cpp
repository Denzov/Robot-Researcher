#include "Graph.h"
#include "countingFuncs.hpp"
#include <deque>
#include <iostream>

using namespace std;
Graph::Graph()
{
}

Graph::~Graph()
{
    delete graph;
    delete walls;
    delete unseen;
}
void Graph::append_vert(Vector2 ver, bool wallIs)
{
    if (graph->find(ver) == graph->end())
    {
        (*graph)[ver] = Vertex(ver, wallIs);
    }
}

void Graph::append_wall(Vector2 ver)
{
    (*walls).push_back(Vertex(ver, true));
    (*graph)[ver] = Vertex(ver, true);
}

vector<Vector2> Graph::find_path(Vector2 from, Vector2 to)
{

    auto front = deque<Vertex>();
    auto visited = map<Vector2, bool, cmpByStringLength>();
    auto path = map<Vector2, Vector2, cmpByStringLength>();
    auto pathReversed = vector<Vector2>();
    front.push_back((*graph)[from]);
    path[from] = from;

    while (front.size() > 0)
    {   
        auto v = front.front();
        front.pop_front();
        if (v.pos.x == to.x && v.pos.y == to.y)
        {
            auto currentV = v.pos;
            pathReversed.push_back(currentV);
            cout << currentV.x << " " << currentV.y << '\n';
            while (!(currentV.x == from.x && currentV.y == from.y))
            {
                currentV = path[currentV];
                cout << currentV.x << " " << currentV.y << '\n';
                pathReversed.push_back(currentV);
            }

            cout << "found path"
                 << "\n";
            return pathReversed;
        }
        if (visited[v.pos])
        {
            continue;
        }

        cout << "processing " << v.pos.x << " " << v.pos.y << "\n";
        for (auto n : v.neighbours)
        {
            auto iterVisited = visited.find(n);
            bool nVisited = iterVisited != visited.end() && visited.find(n)->second == true;
            if ((*graph)[n].isWall && !nVisited)
            {
                visited[n] = true;
            }
            else if (!nVisited)
            {
                front.push_back((*graph)[n]);
                path[n] = v.pos;
                visited[n] = false;
            }
        }
        visited[v.pos] = true;
    }
    
    //path does not exist
    pathReversed.clear();
    return pathReversed;
}

void Graph::makeSeen(Vector2 posEyes, float angle, Vector2 vertexSize)
{
    Vector2 posVertex = roundingToVertSize(countingCoordinates(vertexSize.x * 5, angle, posEyes), vertexSize);
    float k = (posEyes.y - posVertex.y) / (posEyes.x - posVertex.x);
    float b = posEyes.y - k * posEyes.x;
    float xi;
    int count = 40;
    if (posEyes.x > posVertex.x)
    {
        xi = posEyes.x;
        while (count > 1 && !((*graph)[{xi, roundingToVertSize({xi, (k * xi + b)}, vertexSize).y}].isWall)){
            count--;
            unseen->erase({xi, roundingToVertSize({xi, (k * xi + b)}, vertexSize).y});
            xi -= vertexSize.x;
        }
    }
    else
    {
        xi = posEyes.x;
        while (count > 1 && !((*graph)[{xi, roundingToVertSize({xi, (k * xi + b)}, vertexSize).y}].isWall)){
            count--;
            unseen->erase({xi, roundingToVertSize({xi, (k * xi + b)}, vertexSize).y});
            xi += vertexSize.x;
        }
    }
}

Vector2 Graph::countingClosestUnseen(Vector2 posFrom){
    float mindist;
    Vector2 minKey = unseen->begin()->first;
    for (auto i = unseen->begin(); i != unseen->end();)
    {   
        float dist = abs(posFrom.x - i->first.x) + abs(posFrom.y - i->first.y);
        if(i == unseen->begin()){
            mindist = dist;
        }
        else if(mindist > dist){
            mindist = dist;
            minKey = i->first;
        }
    }
    return minKey;
    
}
