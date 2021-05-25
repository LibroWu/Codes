//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;

int n, m, s, t, dist[2505], road[2505][2505], ans;
bool visited[2505];

int main() {
    memset(visited, 0, sizeof(visited));
    cin >> n >> m >> s >> t;
    int u;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j) road[i][j] = ((i == j) ? 0 : 100000000);
    for (int i = 0; i <= n; ++i) dist[i] = 100000000;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        road[u][v] = road[v][u] = c;
    }
    dist[s] = 0;
    for (int i = 1; i <= n; ++i) {
        int res = 100000000;
        for (int j = 0; j <= n; ++j)
            if (!visited[j] && dist[j] < res) {
                u = j;
                res = dist[j];
            }
        if (u == t) break;
        visited[u] = true;
        for (int j = 0; j <= n; ++j) dist[j] = min(dist[j], dist[u]+road[u][j]);
    }
    cout << dist[t];
    return 0;
}