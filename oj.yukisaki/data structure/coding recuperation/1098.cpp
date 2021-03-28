#include<iostream>

using namespace std;

const int N = 500005;
int n, m, a[N], p[N * 8], que[N];


void build(int l, int r, int t) {
    if (l == r) {
        p[t] = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, t << 1);
    build(mid + 1, r, t << 1 | 1);
    p[t] = min(p[t << 1], p[t << 1 | 1]);
}

int get(int l, int r, int x, int y, int t) {
    if (l == x && r == y)
        return p[t];
    int mid = l + r >> 1;
    if (y <= mid) return get(l, mid, x, y, t << 1);
    else if (x > mid) return get(mid + 1, r, x, y, t << 1 | 1);
    else return min(get(l, mid, x, mid, t << 1), get(mid + 1, r, mid + 1, y, t << 1 | 1));
}

int Find(int l, int r) {
    int Min = get(1, n, l, r, 1);
    int x = l, y = r, mid;
    while (x < y) {
        mid = (x + y + 1) >> 1;
        if (get(1, n, mid, r, 1) == Min) x = mid;
        else y = mid - 1;
    }
    return x;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, n, 1);
    int head, tail;
    head = tail = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        while (head < tail && a[que[tail - 1]] < a[i]) --tail;
        que[tail++] = i;
        if (head !=tail) {
            int ll=((tail-2>=head)?que[tail-2]:0)+1;
            if (i==ll) continue;
            int kk = Find(ll, i);
            ans = max(i - kk + 1, ans);
        }
    }
    cout << ans;
}
