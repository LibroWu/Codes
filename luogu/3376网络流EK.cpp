//Luogu P3376
//Edmonds_Karp
//Libro

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int EDGE_NUM = 10005;
const int NODE_NUM = 205;
const long long int INF = 1e12;

struct Edge {
    int next, vet;
    long long int w;
} edge[EDGE_NUM];
int tot = 1;
int Head[NODE_NUM] = {0}, pre[NODE_NUM];
long long int inf[NODE_NUM];
bool visited[NODE_NUM];
int flag[NODE_NUM][NODE_NUM];
void build(int f, int e, int w) {
    edge[++tot].next = Head[f];
    edge[tot].vet = e;
    edge[tot].w = w;
    Head[f] = tot;
}

bool bfs(const int &s, const int &t) {
    memset(visited, 0, sizeof(visited));
    inf[s] = INF;
    visited[s] = 1;
    queue<int> que;
    while (!que.empty()) que.pop();
    que.push(s);
    while (!que.empty()) {
        int u = que.front(), v;
        que.pop();
        for (int i = Head[u]; i; i = edge[i].next) {
            if (edge[i].w) {
                v = edge[i].vet;
                if (visited[v]) continue;
                inf[v] = min(inf[u], edge[i].w);
                pre[v] = i;
                visited[v] = 1;
                que.push(v);
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

long long int update(const int &s, const int &t) {
    int x = t;
    while (x != s) {
        int i = pre[x];
        edge[i].w -= inf[t];
        edge[i ^ 1].w += inf[t];
        x = edge[i ^ 1].vet;
    }
    return inf[t];
}

long long int Edmonds_Karp(const int &s, const int &t) {
    long long int max_flow = 0;
    while (bfs(s, t))
        max_flow += update(s, t);
    return max_flow;
}

int main() {
    memset(flag,0,sizeof(flag));
    int n, m, s, t, x, y, z;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        if (!flag[x][y]) {
            build(x, y, z);
            build(y, x, 0);
            flag[x][y]=tot;
        }
        else{
            edge[flag[x][y]-1].w+=z;
        }
    }
    cout << Edmonds_Karp(s, t);
}