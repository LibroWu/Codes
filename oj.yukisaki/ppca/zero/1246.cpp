#include<iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const long long oo = 1e15;
const int K = 200000;
int Head[4 * K + 100];
struct Node {
    int x, y, num;
};

struct Edge {
    int next, vet, cost;
} edge[10 * K];
int n, m, tot = 0, k, row[K + 5], line[K + 5];
long long ans = 0, dist[K * 4 + 10];
bool inque[K * 4 + 10];
Node nodes[K * 2 + 10];

void build(int u, int v, int cost) {
    if (cost < 0)
        cout << u << ' ' << v << '\n';
    edge[++tot] = Edge({Head[u], v, cost});
    Head[u] = tot;
}

int main() {
    memset(Head, 0, sizeof(Head));
    memset(row, 0, sizeof(row));
    memset(line, 0, sizeof(line));
    memset(inque, 0, sizeof(inque));
    cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) {
        dist[i] = oo;
        dist[i + k] = oo;
        cin >> nodes[i].x >> nodes[i].y;
        nodes[i].num = i;
        build(i, k + i, 1);
        build(k + i, i, 1);
    }
    sort(nodes + 1, nodes + k + 1, [](const Node &a, const Node &b) -> bool { return a.x < b.x; });
    if (nodes[1].x != 1) {
        cout << -1;
        return 0;
    }
    for (int i = 1; i <= k; ++i) {
        if (row[nodes[i].y]) {
            build(nodes[row[nodes[i].y]].num, nodes[i].num, nodes[i].x - nodes[row[nodes[i].y]].x);
            build(nodes[i].num, nodes[row[nodes[i].y]].num, nodes[i].x - nodes[row[nodes[i].y]].x);
        }
        row[nodes[i].y] = i;
    }
    sort(nodes + 1, nodes + k + 1, [](const Node &a, const Node &b) -> bool { return a.y < b.y; });
    for (int i = 1; i <= k; ++i) {
        if (line[nodes[i].x]) {
            build(k + nodes[line[nodes[i].x]].num, k + nodes[i].num, nodes[i].y - nodes[line[nodes[i].x]].y);
            build(k + nodes[i].num, k + nodes[line[nodes[i].x]].num, nodes[i].y - nodes[line[nodes[i].x]].y);
        }
        line[nodes[i].x] = i;
    }
    queue<int> que;
    for (int j = 1; j <= k; ++j)
        if (nodes[j].x == 1) {
            dist[k + nodes[j].num] = nodes[j].y - 1;
            inque[k + nodes[j].num] = true;
            que.push(k + nodes[j].num);
        }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;
        for (int i = Head[u]; i; i = edge[i].next) {
            int v = edge[i].vet;
            if (dist[u] + edge[i].cost < dist[v]) {
                dist[v] = dist[u] + edge[i].cost;
                if (!inque[v]) {
                    inque[v] = true;
                    que.push(v);
                }
            }
        }
    }
    ans = oo;
    for (int i = 1; i <= k; ++i) {
        if (nodes[i].x == n) {
            ans = min(ans, dist[k + nodes[i].num] + m - nodes[i].y);
        }
        if (nodes[i].y == m) {
            ans = min(ans, dist[nodes[i].num] + n - nodes[i].x);
        }
    }
    cout << ((ans == oo) ? -1 : ans);
}