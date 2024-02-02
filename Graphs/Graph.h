#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <map>
#include <vector>
#include <iostream>

typedef uint64_t gr_int;

class Graph{
private:
    std::vector<std::vector<gr_int>>* graph = new std::vector<std::vector<gr_int>>;
    std::vector<bool>* visited = new std::vector<bool>;
    std::vector<gr_int>* path = new std::vector<gr_int>;
public:
    Graph();
    Graph(gr_int n);
    void append_vert();
    void add_edge(gr_int src, std::vector<gr_int> dest);
    bool DFS(gr_int current_vertex, gr_int required_vertex);     
    void print();
    void print_path();
    

};


#endif
