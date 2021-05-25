//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;
const int N = 200005;
const int M = 20000005;
const long long MAXN = 10000000000;
int Head[N], tot, n, p, k, que[N * 100], l, r;
long long dist[N];
bool visited[N];

struct Edge {
    int vet, next;
    long long weight;
} edge[M];

void initialise() {
    memset(Head, 0, sizeof(Head));
    tot = 0;
}

void build(int u, int v, long long weight) {
    edge[++tot].next = Head[u];
    edge[tot].vet = v;
    edge[tot].weight = weight;
    Head[u] = tot;
}

int main() {
    initialise();
    int u, v;
    long long w;
    cin >> n >> p >> k;
    for (int i = 0; i < p; ++i) {
        cin >> u >> v >> w;
        --u;
        --v;
        for (int j = 0; j <= k; ++j) {
            build(j * n + u, j * n + v, w);
            build(j * n + v, j * n + u, w);
        }
        for (int j = 0; j < k; ++j) {
            build(j * n + u, (j + 1) * n + v, 0);
            build(j * n + v, (j + 1) * n + u, 0);
        }
    }
    for (int i = 0; i <= n * (k + 1); ++i) {
        dist[i] = MAXN;
        visited[i] = 0;
    }
    dist[0] = 0;
    l = r = 0;
    que[r++] = 0;
    while (l < r) {
        u = que[l++];
        visited[u] = false;
        for (int i = Head[u]; i; i = edge[i].next) {
            v = edge[i].vet;
            if (max(dist[u],edge[i].weight)<dist[v]) {
                dist[v]=max(dist[u],edge[i].weight);
                if (!visited[v]) {
                    visited[v]=true;
                    que[r++]=v;
                }
            }
        }
    }
    long long ans=MAXN;
    for (int i = 0; i <= k; ++i) {
        ans=min(ans,dist[i*n+n-1]);
    }
    cout<<((ans==MAXN)?-1:ans);
}