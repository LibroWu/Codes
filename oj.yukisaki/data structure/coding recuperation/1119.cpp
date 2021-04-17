//
// Created by LibroNebula on 2021/4/1.
//


#include <iostream>

using namespace std;

const int N = 100005;

double p[N << 3], pp[N << 3], a[N], flag[N << 3];

struct Pair {
    double sum, sqr;

    Pair() = default;

    Pair(double ave, double var) : sum(ave), sqr(var) {}

    Pair operator+(const Pair &other) {
        Pair tmp(*this);
        tmp.sum += other.sum;
        tmp.sqr += other.sqr;
        return tmp;
    }
};

void push_up(int t) {
    p[t] = p[t << 1] + p[t << 1 | 1];
    pp[t] = pp[t << 1] + pp[t << 1 | 1];
}

void push_down(int t, int l, int r) {
    if (flag[t] == 0)
        return;
    int mid = l + r >> 1;
    pp[t << 1] = pp[t << 1] + 2 * flag[t] * p[t << 1] + flag[t] * flag[t] * (mid - l + 1);
    pp[t << 1 | 1] = pp[t << 1 | 1] + 2 * flag[t] * p[t << 1 | 1] + flag[t] * flag[t] * (r - mid);
    p[t << 1] = p[t << 1] + flag[t] * (mid - l + 1);
    p[t << 1 | 1] = p[t << 1 | 1] + flag[t] * (r - mid);
    flag[t << 1] += flag[t];
    flag[t << 1 | 1] += flag[t];
    flag[t] = 0;
}

void build(int l, int r, int t) {
    flag[t] = 0;
    if (l == r) {
        p[t] = a[l];
        pp[t] = a[l] * a[l];
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, t << 1);
    build(mid + 1, r, t << 1 | 1);
    push_up(t);
}

void add(int l, int r, int x, int y, int t, double k) {
    if (l == x && y == r) {
        pp[t] = pp[t] + 2 * k * p[t] + k * k * (y - x + 1);
        p[t] = p[t] + k * (y - x + 1);
        flag[t] += k;
        return;
    }
    push_down(t, l, r);
    int mid = l + r >> 1;
    if (y <= mid) add(l, mid, x, y, t << 1, k);
    else if (x > mid) add(mid + 1, r, x, y, t << 1 | 1, k);
    else {
        add(l, mid, x, mid, t << 1, k);
        add(mid + 1, r, mid + 1, y, t << 1 | 1, k);
    }
    push_up(t);
}

Pair query(int l, int r, int x, int y, int t) {
    if (l == x && r == y) {
        return Pair(p[t], pp[t]);
    }
    push_down(t, l, r);
    int mid = l + r >> 1;
    Pair tmp;
    if (y <= mid) tmp = query(l, mid, x, y, t << 1);
    else if (x > mid) tmp = query(mid + 1, r, x, y, t << 1 | 1);
    else tmp = query(l, mid, x, mid, t << 1) + query(mid + 1, r, mid + 1, y, t << 1 | 1);
    push_up(t);
    return tmp;
}


int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, n, 1);
    int op, x, y, N;
    double k;
    for (int j = 0; j < m; ++j) {
        cin >> op >> x >> y;
        switch (op) {
            case 1:
                cin >> k;
                add(1, n, x, y, 1, k);
                break;
            case 2:
                cout << long(query(1, n, x, y, 1).sum / (y - x + 1) * 100) << '\n';
                break;
            case 3:
                Pair tmp = query(1, n, x, y, 1);
                N = y - x + 1;
                cout << long(100 * (tmp.sqr / N - (tmp.sum / N) * (tmp.sum / N))) << '\n';
        }
    }
}