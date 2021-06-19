#include <iostream>
#include <cstring>

using namespace std;

const int N = 100005;

int father[N], n, m, dist[N];

int getfather(int v) {
    if (father[v] == v) return v;
    int tmp = father[v];
    father[v] = getfather(father[v]);
    dist[v] = dist[v] ^ dist[tmp];
    return father[v];
}

int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        father[i] = i;
        dist[i] = 0;
    }
    int l, r;
    string ch;
    for (int j = 0; j < m; ++j) {
        cin >> l >> r >> ch;
        --l;
        int u = getfather(l), v = getfather(r);
        if (ch[0] == 'e') {
            if (u == v && dist[l] != dist[r]) {
                cout << j + 1;
                return 0;
            }
            if (u != v) {
                father[u] = father[v];
                dist[u] = dist[l] ^ dist[r];
            }
        } else {
            if (u == v && dist[l] == dist[r]) {
                cout << j + 1;
                return 0;
            }
            if (u != v) {
                father[u] = father[v];
                dist[u] = dist[l] ^ dist[r] ^ 1;
            }
        }
    }
    cout << "-1\n";
    return 0;
}