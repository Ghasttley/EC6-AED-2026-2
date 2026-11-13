#include <bits/stdc++.h>

std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> rev_adj;
        std::vector<bool> visited;
            std::vector<int> component_id;
                std::stack<int> order;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) { dfs1(v); }
    } order.push(u);
}

void dfs2(int u, int comp) {
    component_id[u] = comp;
    for (int v : rev_adj[u]) {
        if (component_id[v] == -1) { dfs2(v, comp); }
    }
}

int main() {
    int n, m; if (!(std::cin >> n >> m)) return 0;

    adj.resize(n + 1);
        rev_adj.resize(n + 1);
            visited.assign(n + 1, false);
                component_id.assign(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v; std::cin >> u >> v;
        adj[u].push_back(v);
            rev_adj[v].push_back(u); // Grafo transpuesto
    }

    for (int i = 1; i <= n; ++i) { if (!visited[i]) { dfs1(i); } }

    int num_components = 0;
    while (!order.empty()) {
        int u = order.top(); order.pop();
        if (component_id[u] == -1) {
            dfs2(u, num_components); num_components++;
        }
    }

    std::vector<int> out_degree(num_components, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (component_id[u] != component_id[v]) {
                out_degree[component_id[u]]++;
            }
        }
    }

    int sinks = 0; int sink_comp_id = -1;
    for (int i = 0; i < num_components; ++i) {
        if (out_degree[i] == 0) {
            sinks++; sink_comp_id = i;
        }
    }

    if (sinks == 1) {
        int leader_count = 0;
        for (int i = 1; i <= n; ++i) {
            if (component_id[i] == sink_comp_id) { leader_count++; }
        } std::cout << leader_count << "\n";
    } else { std::cout << 0 << "\n"; }
    return 0;
}