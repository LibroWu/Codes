//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;
const int N = 10005;
const int M = 1000005;
int weight[N], father[N];

struct Edge {
    int l, r, weight;

    bool operator<(const Edge &other) {
        return weight < other.weight;
    }
} a[M], b[M];

void mergeSort(int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    int x = l, y = mid + 1, k = l;
    while (x <= mid && y <= r) {
        if (a[x] < a[y]) b[k++] = a[x++];
        else b[k++] = a[y++];
    }
    while (x <= mid) b[k++] = a[x++];
    while (y <= r) b[k++] = a[y++];
    for (int i = l; i <= r; ++i) {
        a[i] = b[i];
    }
}

int getFather(int v) {
    if (father[v] == v) return v;
    return father[v] = getFather(father[v]);
}

int main() {
    int n, m, Min = 1000000;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        cin >> weight[i];
        Min= min(Min,weight[i]);
    }
    for (int i = 0; i < m; ++i) {
        cin >> a[i].l >> a[i].r >> a[i].weight;
        a[i].weight<<=1;
        a[i].weight += weight[a[i].l] + weight[a[i].r];
    }
    long long ans = 0;
    int cnt=0;
    mergeSort(0, m - 1);
    for (int i = 0; i < m; ++i) {
        int u = getFather(a[i].l), v = getFather(a[i].r);
        if (u != v) {
            ++cnt;
            father[u] = father[v];
            ans += a[i].weight;
            if (cnt==n-1) break;
        }
    }
    cout<<ans+Min;
}