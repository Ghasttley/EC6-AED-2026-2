#include <bits/stdc++.h>

std::vector<std::vector<int>> adj;
    std::vector<int> parent; 
        std::vector<bool> visited;

// DFS para encontrar el camino desde el nodo 1 hasta el nodo t
bool dfs(int u, int target) {
    if (u == target) return true;
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
                if (dfs(v, target)) { return true; }
        }
    } return false;
}

int main() {
    int n, t; if (!(std::cin >> n >> t)) return 0;

    adj.resize(n + 1);
        parent.assign(n + 1, -1);
            visited.assign(n + 1, false);

    for (int i = 0; i < n - 1; ++i) {
        int u, v; std::cin >> u >> v;
        // conectar ambos sentidos
        adj[u].push_back(v);
        adj[v].push_back(u);
    } dfs(1, t);

    std::vector<int> path; int curr = t;
    while (curr != -1) {
        path.push_back(curr);
            if (curr == 1) break;
                curr = parent[curr];
    }

    reverse(path.begin(), path.end());

    std::cout << path.size() << "\n";
    
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i == path.size() - 1 ? "" : " ");
    } std::cout << "\n";

    return 0;
}