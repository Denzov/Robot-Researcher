#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <map>

#include "Vertex.h"



class Graph{
protected:
    std::vector<Vertex>* graph;
    std::vector<bool>* visited;
    std::vector<gr_int>* path;

public:
    Graph();
    ~Graph();
    Graph(gr_int n);
    void append_vert(float x, float y);
//    void add_edge(gr_int src, std::vector<gr_int> dest);
    bool DFS(gr_int current_vertex, gr_int required_vertex);     
    std::vector<gr_int>* Get_Path();

    void print();
    void print_path();
    

};


#endif
