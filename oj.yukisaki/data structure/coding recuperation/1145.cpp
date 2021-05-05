//
// Created by Libro on 2021/4/26.
//

#include <iostream>

using namespace std;

const int N = 200005;

int p[N << 2], a[N], n, m;

void build(int l, int r, int t) {
    if (l == r) {
        p[t] = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, t << 1);
    build(mid + 1, r, t << 1 | 1);
    p[t] = max(p[t << 1], p[t << 1 | 1]);
}

int query(int l, int r, int x, int y, int t) {
    if (l == x && y == r)return p[t];
    int mid = l + r >> 1;
    if (mid >= y) return query(l, mid, x, y, t << 1);
    if (mid < x) return query(mid + 1, r, x, y, t << 1 | 1);
    return max(query(l, mid, x, mid, t << 1), query(mid + 1, r, mid + 1, y, t << 1 | 1));
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, n, 1);
    cin>>m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        cout << query(1, n, x, y, 1) << '\n';
    }
}