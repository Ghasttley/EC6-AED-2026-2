#include <bits/stdc++.h>
// from el ppt de progra III

template <typename T>
struct Graph{
    std::unordered_map<T, std::unordered_map<T, int>> g_map;

    void new_edge(T a, T b, int peso){
        g_map[a][b] = peso;
        g_map[b][a] = peso;
    }

    std::unordered_map<T, int> dijkstra(T u){
        std::unordered_map<T, int> dists;
        for(const auto& i : g_map) dists[i.first] = INT_MAX;
        // Para asegurar que el nodo origen exista
        dists[u] = 0;

        // min-heap usando pares negativos (pair<int,T>)
        std::priority_queue<std::pair<int, T>> non_visited;
        non_visited.push({0, u});

        while(!non_visited.empty()){
            auto [neg_dist, v] = non_visited.top(); non_visited.pop();
            int d = -neg_dist; if(d > dists[v]) continue;

            for(const auto& i : g_map[v]){
                T vecino = i.first;
                int w = i.second;
                if(dists[vecino] > dists[v] + w){
                    dists[vecino] = dists[v] + w;
                    non_visited.push({-dists[vecino], vecino});
                }
            }
        }
        return dists;
    }
};

int main(){
    Graph<char> g;

    g.new_edge('A','C', 4);
    g.new_edge('A','D', 7);
    g.new_edge('C','D', 11);
    g.new_edge('C','E', 20);
    g.new_edge('C','F', 9);
    g.new_edge('D','E', 1);
    g.new_edge('E','G', 1);
    g.new_edge('E','I', 3);
    g.new_edge('F','G', 2);
    g.new_edge('F','H', 6);
    g.new_edge('G','H', 10);
    g.new_edge('G','B', 15);
    g.new_edge('G','I', 5);
    g.new_edge('H','B', 5);
    g.new_edge('I','B', 12);

    auto dists = g.dijkstra('A');

    // Imprime resultados ordenados
    std::vector<std::pair<char,int>> res(dists.begin(), dists.end());
    std::sort(res.begin(), res.end());
    for(auto& [nodo, d] : res){
        std::cout << nodo << "->" << d << "\n";
    }

    // Salida: A->0,B->22,C->4,D->7,E->8,F->11,G->9,H->17,I->11

    return 0;
}