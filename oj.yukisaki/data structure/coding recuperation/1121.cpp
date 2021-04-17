//
// Created by LibroNebula on 2021/4/1.
//
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100005;

struct Edge {
    int next, vet, weight;
} edge[N << 1];

int Head[N], tot = 0, parent[N][20], Log[N], w1[N][20], w2[N][20], depth[N];
struct Pair {
    int sum, xor_sum;
};

void build(int u, int v, int w) {
    edge[++tot].next = Head[u];
    edge[tot].vet = v;
    edge[tot].weight = w;
    Head[u] = tot;
}

void prepare(int u, int pa) {
    int v;
    for (int i = 1; i < 20; ++i) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
        w1[u][i] = w1[u][i - 1] + w1[parent[u][i - 1]][i - 1];
        w2[u][i] = w2[u][i - 1] ^ w2[parent[u][i - 1]][i - 1];
    }
    for (int i = Head[u]; i; i = edge[i].next) {
        v = edge[i].vet;
        if (v == pa) continue;
        parent[v][0] = u;
        w1[v][0] = edge[i].weight;
        w2[v][0] = edge[i].weight;
        depth[v] = depth[u] + 1;
        prepare(v, u);
    }
}

Pair lca(int u, int v) {
    Pair tmp;
    tmp.sum = tmp.xor_sum = 0;
    if (depth[u] < depth[v]) {
        int kk = u;
        u = v;
        v = kk;
    }
    for (int i = Log[depth[u]]; i >= 0; --i) {
        if (depth[parent[u][i]] >= depth[v]) {
            tmp.sum += w1[u][i];
            tmp.xor_sum ^= w2[u][i];
            u = parent[u][i];
        }
        if (u == v) return tmp;
    }
    for (int i = Log[depth[u]]; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            tmp.sum += w1[u][i] + w1[v][i];
            tmp.xor_sum ^= w2[u][i] ^ w2[v][i];
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    int i = 0;
    tmp.sum += w1[u][i] + w1[v][i];
    tmp.xor_sum ^= w2[u][i] ^ w2[v][i];
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    memset(Head, 0, sizeof(Head));
    memset(parent, 0, sizeof(parent));
    memset(w1, 0, sizeof(w1));
    memset(w2, 0, sizeof(w2));;
    memset(depth, 0, sizeof(depth));
    Log[0] = Log[1] = 0;
    for (int i = 2; i < N; ++i) {
        Log[i] = Log[i >> 1] + 1;
    }
    int n, m, x, y, z;
    cin >> n >> m;
    for (int j = 0; j < n-1; ++j) {
        cin >> x >> y >> z;
        build(x, y, z);
        build(y, x, z);
    }
    prepare(1, 0);
    for (int k = 0; k < m; ++k) {
        cin >> x >> y >> z;
        if (x == 0) cout << lca(y, z).xor_sum << '\n';
        else cout << lca(y, z).sum << '\n';
    }
}