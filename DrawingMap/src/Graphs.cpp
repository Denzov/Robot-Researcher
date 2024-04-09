#include "Graph.h"

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
    (*walls)[ver] = Vertex(ver, true);
    (*graph)[ver] = Vertex(ver, true);
}