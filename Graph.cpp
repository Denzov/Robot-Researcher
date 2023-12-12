#include <iostream>
#include <list>
#include <set>
#include <map>
class Graph{
private:
    std::map<uint64_t, std::set<uint64_t>>* graph = new std::map<uint64_t, std::set<uint64_t>>;

public:

};

int main(){
    std::list<int> n = {2};
    n.insert(125);
    n.insert(12);
    n.insert(1);
    std::cout<<"[START]\n";
    for (auto i : n){
        std::cout << i << ' ';
    }
    std::cout<<'\n';
    std::cout<<"[END]\n";
}