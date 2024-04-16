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

    cout << "ended";
    pathReversed.clear();
    return pathReversed;
}

bool Graph::makeSeen(Vector2 posEyes, Vector2 posVertex, Vector2 vertexSize)
{
    float k = (posEyes.y - posVertex.y) / (posEyes.x - posVertex.x);
    float b = posEyes.y - k * posEyes.x;
    if (posEyes.x > posVertex.x)
    {
        for(float xi = posEyes.x; xi > posVertex.x; xi -= vertexSize.x){
            (*graph)[{xi, roundingToVertSize({xi, (k * xi + b)}, vertexSize).y}].seen = true;
        }
    }
    else
    {
        for(float xi = posEyes.x; xi < posVertex.x; xi += vertexSize.x){
            (*graph)[{xi, roundingToVertSize({xi, (k * xi + b)}, vertexSize).y}].seen = true;
        }
    }
}
