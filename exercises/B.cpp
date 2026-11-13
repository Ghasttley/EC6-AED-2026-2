#include <bits/stdc++.h>
const long long INF = 1e18;

struct Edge {
    int to;
    long long weight;
};

// Algoritmo de Dijkstra
std::vector<long long> dijkstra(int start, int n, const std::vector<std::vector<Edge>>& adj) {
    std::vector<long long> dist(n + 1, INF);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;

    dist[start] = 0; pq.push({0, start});

    while (!pq.empty()) {
        long long d = pq.top().first;
            int u = pq.top().second;
                pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.to; long long w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
            }
        }
    } return dist;
}

int main() {
    int n, m; long long T;
    if (!(std::cin >> n >> m >> T)) return 0;

    std::vector<std::vector<Edge>> adj(n + 1);
    std::vector<std::vector<Edge>> rev_adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v; long long w;
        std::cin >> u >> v >> w;
        
        adj[u].push_back({v, w});
        rev_adj[v].push_back({u, w});
    }

    std::vector<long long> dist_ida = dijkstra(1, n, adj);
    std::vector<long long> dist_vuelta = dijkstra(1, n, rev_adj);

    int empleados_count = 0; long long total_minutos = 0;

    for (int i = 1; i <= n; ++i) {
        if (dist_ida[i] <= T && dist_vuelta[i] <= T) {
            empleados_count++;
                total_minutos += dist_ida[i] + dist_vuelta[i];
        }
    } std::cout << empleados_count << " " << total_minutos << "\n";

    return 0;
}