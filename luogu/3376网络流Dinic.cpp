//Luogu P3376
//Dinic
//Libro

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int EDGE_NUM = 240005;
const int NODE_NUM = 1205;
const long long int INF = 1e18;

struct EDGE {
    int next, vet;
    long long int w;
} edge[EDGE_NUM];

int head[NODE_NUM], d[NODE_NUM], now[NODE_NUM];
int tot = 1, t;
int flag[NODE_NUM][NODE_NUM];

void build(int u, int v, long long int k) {
    edge[++tot].next = head[u];
    edge[tot].vet = v;
    edge[tot].w = k;
    head[u] = tot;
}

bool bfs(const int &s, const int &t) {
    memset(d, 0, sizeof(d));
    queue<int> que;
    while (!que.empty()) que.pop();
    que.push(s);
    d[s] = 1;
    now[s] = head[s];
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].vet;
            if (!edge[i].w || d[v]) continue;
            que.push(v);
            now[v] = head[v];
            d[v] = d[u] + 1;
            if (v == t) return 1;
        }
    }
    return 0;
}

long long int dinic(int x, long long int flow) {
    if (x == t) return flow;
    long long int rest = flow,k;
    int i, v;
    for (i = now[x]; i && rest; i = edge[i].next)
        if (edge[i].w && d[v = edge[i].vet] == d[x] + 1) {
            k = dinic(v, min(rest, edge[i].w));
            if (!k) d[v] = 0;
            edge[i].w -= k;
            edge[i ^ 1].w += k;
            rest -= k;
        }
    now[x] = i;
    return flow - rest;
}

int main() {
    memset(flag, 0, sizeof(flag));
    int n, m, s, u, v;
    long long int k;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> k;
        if (!flag[u][v]) {
            build(u, v, k);
            flag[u][v] = tot;
            build(v, u, 0);
            flag[v][u] = tot;
        }
        else edge[flag[u][v]].w += k;
    }
    long long int flow = 0, max_flow = 0;
    while (bfs(s, t))
        while (flow = dinic(s, INF)) max_flow += flow;
    cout << max_flow << endl;
}