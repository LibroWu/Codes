//
// Created by Libro on 2021/5/24.
//

#include <iostream>

using namespace std;

int n, dist[305], road[305][305], ans;
bool visited[305];

int main() {
    cin >> n;
    dist[0] = 0;
    visited[0] = 0;
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> road[0][i];
        dist[i] = road[i][0] = road[0][i];
        visited[i] = false;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> road[i][j];
        }
    int u=0;
    for (int i = 0; i <= n; ++i) {
        int res=10000000;
        for (int j = 0; j <= n; ++j)
            if (!visited[j] && dist[j]<res) {
                u=j;
                res=dist[j];
            }
        visited[u]= true;
        ans+=dist[u];
        for (int j = 0; j <= n; ++j) dist[j]= min(dist[j],road[u][j]);
    }
    cout<<ans;
    return 0;
}