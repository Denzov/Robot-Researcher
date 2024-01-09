#include "Graph.h"

void Graph::Graph(uint64_t n){
    for(uint64_t i = 0; i < n; i++){
        std::set<uint64_t> a {0};
        graph[i] = a;
    }
}
void Graph::push_vertex(){

}