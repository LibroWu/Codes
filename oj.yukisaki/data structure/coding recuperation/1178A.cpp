//
// Created by Libro on 2021/5/10.
//

#include <iostream>
#include <cstring>

using namespace std;
const int N = 100005;
int Head[N], d[N], tot = 0, queue[N], D[N], l, r;
struct Edge {
    int vet, next;
} edge[N * 100];

struct Double {
    __int128 p, q;

    __int128 gcd(__int128 x, __int128 y) {
        if (x % y == 0) return y;
        return gcd(y, x % y);
    }

    Double() : p(0), q(1) {}

    Double operator+(const Double &other) {
        Double tmp;
        __int128 GCD = gcd(tmp.q, q);
        tmp.q = q / GCD * other.q;
        tmp.p = tmp.q / q * p + tmp.q / other.q * other.p;
        GCD = gcd(tmp.q, tmp.p);
        tmp.q /= GCD, tmp.p /= GCD;
        return tmp;
    }

    Double &operator+=(const Double &other) {
        return *this = *this + other;
    }

    Double operator/(__int128 d) {
        Double tmp(*this);
        __int128 GCD = gcd(tmp.p, d);
        tmp.p /= GCD, d /= GCD, tmp.q *= d;
        return tmp;
    }

    Double &operator/=(__int128 d) {
        return *this = *this / d;
    }
} ans[N];

void build(int u, int v) {
    ++d[v];
    ++D[u];
    edge[++tot].next = Head[u];
    edge[tot].vet = v;
    Head[u] = tot;
}

void print(__int128 x) {
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    memset(Head, 0, sizeof(Head));
    memset(d, 0, sizeof(d));
    memset(D, 0, sizeof(D));
    memset(Head, 0, sizeof(Head));
    int n, m, di, v;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> di;
        while (di--) {
            cin >> v;
            build(i, v);
        }
    }
    l = r = 0;
    for (int i = 1; i <= n; ++i)
        if (d[i] == 0) {
            queue[r++] = i;
            ans[i].p = ans[i].q = 1;
        }
    while (l < r) {
        int u = queue[l++];
        for (int i = Head[u]; i; i = edge[i].next) {
            v = edge[i].vet;
            --d[v];
            ans[v] += ans[u] / D[u];
            if (d[v] == 0) queue[r++] = v;
        }
    }
    for (int i = 1; i <= n; ++i) if (D[i] == 0) print(ans[i].p),cout<<' ', print(ans[i].q),cout<<'\n';
}