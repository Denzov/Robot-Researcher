#include "Graph.h"

Graph::Graph(gr_int n)
{
    graph = new std::vector<std::vector<gr_int>>;
    visited = new std::vector<bool>;
    path = new std::vector<gr_int>;
    
    for (gr_int i = 0; i < n; i++)
    {
        append_vert();
    }
}

Graph::~Graph(){
    delete graph;
    delete visited;
    delete path;

}
void Graph::append_vert()
{
    graph->push_back(std::vector<gr_int>());
    visited->push_back(false);
}
void Graph::add_edge(gr_int src, std::vector<gr_int> dest)
{
    (*graph)[src] = dest;
}
bool Graph::DFS(gr_int current_vertex, gr_int required_vertex)
{
    (*visited)[current_vertex] = true;
    
    if (current_vertex == required_vertex)
    {
    
        path->push_back(current_vertex);
        return true;
    }

    for (gr_int i = 0; i != (*graph)[current_vertex].size(); i++)
    {
        if (!(*visited)[(*graph)[current_vertex][i]])
        {
            if(DFS((*graph)[current_vertex][i], required_vertex))
            {
                path->push_back(current_vertex);
                return true;
            }
        }
    }
    return false;
}

void Graph::print()
{
    int n = 0;
    for (auto i : *graph)
    {

        std::cout << n++ << ": ";

        for (auto j : i)
        {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
}

void Graph::print_path(){
    for(auto vertex : *path)
    {
        std::cout << vertex << " ";
    }
}

std::vector<gr_int>* Graph::Get_Path(){
    return path;
}