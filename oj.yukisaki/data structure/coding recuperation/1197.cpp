//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;

const int N = 2000005;
const int M = 2000005;

int n, m, s, p, DFN[N], low[N], cnt = 0, colorNum = 0, color[N], st[N], top = 0;
long long value[N], Value[N], ans = 0,dp[N];
bool hasBar[N], HasBar[N], visited[N];

struct AdjacencyList {
    int Head[N], tot,d[N];

    struct Edge {
        int vet, next;
    } edge[M];

    void initialise() {
        memset(d,0, sizeof(d));
        memset(Head, 0, sizeof(Head));
        tot = 0;
    }

    void build(int u, int v) {
        edge[++tot].next = Head[u];
        edge[tot].vet = v;
        Head[u] = tot;
        ++d[v];
    }
} origin, afterTarjan;

void tarjan(int u) {
    DFN[u] = low[u] = ++cnt;
    st[top++] = u;
    int v;
    for (int i = origin.Head[u]; i; i = origin.edge[i].next) {
        v = origin.edge[i].vet;
        if (!DFN[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!color[v]) low[u] = min(low[u], DFN[v]);
    }
    if (DFN[u] == low[u]) {
        ++colorNum;
        Value[colorNum] = 0;
        while (st[top] != u) {
            Value[colorNum] += value[st[top - 1]];
            HasBar[colorNum] |= hasBar[st[top - 1]];
            color[st[--top]] = colorNum;
        }
    }
}

void dfs(int u) {
    visited[u] = true;
    if (HasBar[u]) ans = max(dp[u], ans);
    int v;
    for (int i = afterTarjan.Head[u]; i; i = afterTarjan.edge[i].next) {
        v = afterTarjan.edge[i].vet;
        --afterTarjan.d[v];
        dp[v]= max(dp[v],dp[u]);
        if (!afterTarjan.d[v]) {
            dp[v]+=Value[v];
            dfs(v);
        }
    }
}

int main() {
    memset(visited, 0, sizeof(visited));
    memset(hasBar, 0, sizeof(hasBar));
    memset(HasBar, 0, sizeof(HasBar));
    memset(color, 0, sizeof(color));
    memset(st, 0, sizeof(st));
    memset(DFN, 0, sizeof(DFN));
    memset(dp, 0, sizeof(dp));
    origin.initialise();
    afterTarjan.initialise();
    cin >> n >> m;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        origin.build(u, v);
    }
    for (int i = 1; i <= n; ++i) cin >> value[i];
    cin >> s >> p;
    for (int i = 0; i < p; ++i) {
        cin >> u;
        hasBar[u] = true;
    }
    tarjan(s);
    for (u = 1; u <= n; ++u)
        if (color[u]) {
            for (int i = origin.Head[u]; i; i = origin.edge[i].next) {
                v = origin.edge[i].vet;
                if (color[v] && color[v] != color[u]) afterTarjan.build(color[u], color[v]);
            }
        }
    dp[color[s]]=Value[color[s]];
    dfs(color[s]);
    cout << ans;
}