#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <map>
#include <vector>
#include <iostream>

typedef uint64_t gr_int;

class Graph{
protected:
    std::vector<std::vector<gr_int>>* graph;
    std::vector<bool>* visited;
    std::vector<gr_int>* path;
    
public:
    Graph();
    ~Graph();
    Graph(gr_int n);
    void append_vert();
    void add_edge(gr_int src, std::vector<gr_int> dest);
    bool DFS(gr_int current_vertex, gr_int required_vertex);     
    std::vector<gr_int>* Get_Path();

    void print();
    void print_path();
    

};


#endif
