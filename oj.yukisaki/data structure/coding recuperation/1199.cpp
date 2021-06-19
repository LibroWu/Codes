#include <iostream>
#include <cstring>

using namespace std;

double MAXT = 1000000000;
int Head[155], tot = 0, n, m, d, l, r,ANS[155],cnt=0;
double dp[155][505];
bool in_que[155][505];

struct Edge {
    int next, vet, v, l;
} edge[100005];

void build(int a, int b, int v, int l) {
    edge[++tot].next = Head[a];
    edge[tot].vet = b;
    edge[tot].v = v;
    edge[tot].l = l;
    Head[a] = tot;
}

struct Pair {
    int n, v;

    Pair(int n=-1, int v=-1) : n(n), v(v) {}
} queue[2000005],from[155][505];

int main() {
    memset(Head, 0, sizeof(Head));
    cin >> n >> m >> d;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 501; ++j) dp[i][j] = MAXT;
    for (int i = 0; i < m; ++i) {
        int a, b, v, l;
        cin >> a >> b >> v >> l;
        build(a, b, v, l);
    }
    dp[0][70] = 0;
    l = r = 0;
    queue[r++] = Pair(0, 70);
    in_que[0][70] = true;
    while (l < r) {
        Pair tmp = queue[l++];
        int u = tmp.n;
        in_que[u][tmp.v]=false;
        for (int i = Head[u]; i; i = edge[i].next) {
            int v = edge[i].vet;
            int V = ((edge[i].v) ? edge[i].v : tmp.v);
            double time = double(edge[i].l) / V;
            if (dp[u][tmp.v] + time < dp[v][V]) {
                dp[v][V] = dp[u][tmp.v] + time;
                if (!in_que[v][V]) {
                    in_que[v][V] = true;
                    queue[r++] = Pair(v, V);
                }
                from[v][V]=tmp;
            }
        }
    }
    double ans=MAXT;
    int j=0;
    for (int i = 0; i < 501; ++i)
        if (dp[d][i]<ans) {
            ans=dp[d][i];
            j=i;
        }
    int k=d;
    while (from[k][j].n!=-1) {
        ANS[cnt++]=k;
        Pair tmp=from[k][j];
        k=tmp.n;
        j=tmp.v;
    }
    ANS[cnt]=0;
    for (int i = cnt; i >=0 ; --i) cout<<ANS[i]<<' ';
    return 0;
}