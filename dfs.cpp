#include <bits/stdc++.h>
// from el ppt de progra III

template <typename T>
struct Graph{
    std::unordered_map<T, std::unordered_set<T>> g_map;
    void new_edge(T a, T b){
        g_map[a].insert(b); g_map[b].insert(a);
    }

    std::vector<T> DFS(T u){
        std::stack<T> s;
        s.push(u);
        std::unordered_set<T> visited;
        std::vector<T> order;

        while(!s.empty()){
            T top = s.top(); s.pop();
            if(visited.find(top) == visited.end()){
                visited.insert(top);
                order.push_back(top);
                for(const T &next: g_map[top]){
                    if(visited.find(next) == visited.end()) s.push(next);
                }
            }
        }
        return order;
    }
};

int main(){
    Graph<char> g;
    g.new_edge('A', 'B');
    g.new_edge('A', 'C');
    g.new_edge('B', 'C');
    g.new_edge('B', 'D');
    g.new_edge('C', 'E');

    std::vector<char> orden = g.DFS('A');

    for(char c : orden) std::cout << c << " ";
    std::cout << "\n"; // A C E B D ish

    return 0;
}