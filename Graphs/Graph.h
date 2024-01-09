#ifndef _GRAPH_H_ 
#define _GRAPH_H_

#include <set>
#include <map>

class Graph{
private:
    std::map<uint64_t, std::set<uint64_t>>* graph = new std::map<uint64_t, std::set<uint64_t>>;
    
    

public:
    Graph(uint64_t n);
    void push_vertex();
};


#endif
