//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;
const int N = 200005;
const long long MAXN = 2000000000005;
int n, m, s, tot = 0, q, c[N], Head[N], que[N * 10], l, r, Near[N], U[N], V[N], D[N], father[N];
bool in_que[N], ans[N];
long long dist[N];

struct Edge {
    int vet, next, d;
} edge[N * 2];

struct Query {
    int x, y, number;
    long long b;
} query[N], b[N], connection[N];

int getFather(int v) {
    if (father[v] == v) return v;
    return father[v] = getFather(father[v]);
}

void build(int u, int v, int d) {
    edge[++tot].next = Head[u];
    edge[tot].vet = v;
    edge[tot].d = d;
    Head[u] = tot;
}

void mergeSort(int l, int r, Query *a) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid, a);
    mergeSort(mid + 1, r, a);
    int x = l, y = mid + 1, k = l;
    while (x <= mid && y <= r) {
        if (a[x].b < a[y].b) b[k++] = a[x++];
        else b[k++] = a[y++];
    }
    while (x <= mid) b[k++] = a[x++];
    while (y <= r) b[k++] = a[y++];
    for (int i = l; i <= r; ++i)
        a[i] = b[i];
}

int main() {
    memset(Head, 0, sizeof(Head));
    memset(Near, 0, sizeof(Near));
    memset(in_que, 0, sizeof(in_que));
    memset(ans, 0, sizeof(ans));
    cin >> n >> s >> m;
    for (int i = 1; i <= n; ++i) dist[i] = MAXN;
    for (int i = 0; i < s; ++i) {
        cin >> c[i];
        build(0, c[i], 0);
    }
    for (int i = 0; i < m; ++i) {
        cin >> U[i] >> V[i] >> D[i];
        build(U[i], V[i], D[i]);
        build(V[i], U[i], D[i]);
    }
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> query[i].x >> query[i].y >> query[i].b;
        query[i].number = i;
    }
    mergeSort(0, q - 1, query);
    dist[0] = 0;
    l = r = 0;
    que[r++] = 0;
    while (l < r) {
        int u = que[l++];
        in_que[u] = false;
        for (int i = Head[u]; i; i = edge[i].next) {
            int v = edge[i].vet;
            if (dist[u] + edge[i].d < dist[v]) {
                dist[v] = dist[u] + edge[i].d;
                if (!in_que[v]) {
                    in_que[v] = true;
                    que[r++] = v;
                }
                if (u == 0) Near[v] = v;
                else Near[v] = Near[u];
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        connection[i].x = Near[U[i]];
        connection[i].y = Near[V[i]];
        connection[i].b = dist[U[i]] + dist[V[i]] + D[i];
    }
    mergeSort(0, m - 1, connection);
    int k = 0;
    for (int i = 0; i < n; ++i) father[i] = i;
    for (int i = 0; i < q; ++i) {
        while (k < m && connection[k].b <= query[i].b) {
            int u = getFather(connection[k].x), v = getFather(connection[k].y);
            if (u != v) father[u] = v;
            ++k;
        }
        int u = getFather(query[i].x), v = getFather(query[i].y);
        ans[query[i].number]=(u==v);
    }
    for (int i = 0; i < q; ++i) cout<<((ans[i])?"TAK\n":"NIE\n");
}