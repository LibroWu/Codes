//
// Created by Libro on 2021/6/5.
//

#include <iostream>
#include <cstring>

using namespace std;
const int N = 300005;
int n, m, HEAD[N], tot = 0, Euler[N * 2], cnt = 0, count = 0;
int parent[N][20], depth[N], t[N * 2];

struct Edge {
    int next, vet;
} edge[N * 2];

struct Pair {
    int first, second;
} P[N], conflict[N];

void build(int u, int v) {
    edge[++tot].next = HEAD[u];
    edge[tot].vet = v;
    HEAD[u] = tot;
}

void prepare(int u, int pa) {
    Euler[++cnt] = u;
    P[u].first = cnt;
    parent[u][0] = pa;
    for (int i = 0; i < 19; ++i) parent[u][i + 1] = parent[parent[u][i]][i];
    depth[u] = depth[pa] + 1;
    for (int i = HEAD[u]; i; i = edge[i].next) {
        int v = edge[i].vet;
        if (v == pa) continue;
        prepare(v, u);
    }
    Euler[++cnt] = u;
    P[u].second = cnt;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int c = u;
        u = v, v = c;
    }
    for (int i = 19; i >= 0; --i)
        if (depth[parent[u][i]] >= depth[v])
            u = parent[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i)
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    return parent[u][0];
}

inline int lowbit(int x) {
    return x & -x;
}

int query(int x) {
    int tmp = 0;
    while (x) {
        tmp += t[x];
        x -= lowbit(x);
    }
    return tmp;
}

void add(int x, int k) {
    while (x <= 2 * n) {
        t[x] += k;
        x += lowbit(x);
    }
}

int main() {
    memset(HEAD, 0, sizeof(HEAD));
    memset(t, 0, sizeof(t));
    cin >> n >> m;
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        build(u, v);
        build(v, u);
    }
    depth[0] = 0;
    for (int i = 0; i < 20; ++i) parent[0][i] = 0;
    prepare(1, 0);
    char op;
    int x, y, pa;
    for (int i = 0; i < m; ++i) {
        cin >> op;
        switch (op) {
            case 'Q':
                cin >> x >> y;
                pa = lca(x, y);
                cout << (((query(P[x].first) + query(P[y].first) - 2 * query(P[pa].first)) == 0) ? "Yes\n" : "No\n");
                break;
            case 'C':
                cin >> x >> y;
                if (depth[x] > depth[y]) {
                    add(P[x].first, 1);
                    add(P[x].second, -1);
                    conflict[count].first = x;
                    conflict[count++].second = y;
                } else {
                    add(P[y].first, 1);
                    add(P[y].second, -1);
                    conflict[count].first = y;
                    conflict[count++].second = x;
                }
                break;
            case 'U':
                cin >> x;
                add(P[conflict[x - 1].first].first, -1);
                add(P[conflict[x - 1].first].second, 1);
                break;
        }
    }
}