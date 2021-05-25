//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;

const int N = 10005;
const int M = 10005;
int Head[N], tot, n, m, d[N], D[N], que[N], C[N], U[N], l, r;
bool visited[N];

struct Edge {
    int vet, weight, next;
} edge[M];

void initialise() {
    memset(visited, 0, sizeof(visited));
    memset(d, 0, sizeof(d));
    memset(D, 0, sizeof(D));
    memset(Head, 0, sizeof(Head));
    tot = 0;
}

void build(int u, int v, int weight) {
    edge[++tot].next = Head[u];
    edge[tot].vet = v;
    edge[tot].weight = weight;
    ++d[v];
    ++D[u];
    Head[u] = tot;
}

int main() {
    initialise();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> C[i] >> U[i];
        C[i] -= U[i];
    }
    int u, v, w;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        build(u, v, w);
    }
    int l = r = 0;
    for (int i = 1; i <= n; ++i)
        if (!d[i]) {
            que[r++] = i;
            C[i] += U[i];
        }
    while (l < r) {
        u = que[l++];
        for (int i = Head[u]; i; i = edge[i].next) {
            v = edge[i].vet;
            if (C[u] > 0)C[v] += C[u] * edge[i].weight;
            --d[v];
            if (!d[v]) que[r++] = v;
        }
    }
    bool flag = false;
    for (int i = 1; i <= n; ++i)
        if (!D[i] && C[i] > 0) {
            cout << i << ' ' << C[i] << '\n';
            flag = true;
        }
    if (!flag) cout << "NULL\n";
}