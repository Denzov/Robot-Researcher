#include <iostream>
#include "Graph.h"

int main(){
    std::cout<<"[START]\n";

    Graph graph(7);
    std::cout<<"[GRAPH]\n";

    graph.add_edge(0, {2, 3});
    graph.add_edge(1, {3});
    graph.add_edge(2, {0});
    graph.add_edge(3, {0, 1, 4, 5, 6});
    graph.add_edge(4, {3});
    graph.add_edge(5, {3, 6});
    graph.add_edge(6, {3, 5});
    std::cout<<"[PRINT]\n";
    graph.print();

    graph.DFS(1, 6);
    
    std::cout<<'\n';
    std::cout<<"[END]\n";

}