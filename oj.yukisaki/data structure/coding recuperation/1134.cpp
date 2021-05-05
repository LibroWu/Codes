//
// Created by Libro on 2021/4/17.
//

#include <iostream>
#include <queue>

using namespace std;

struct Pair {
    long long num, v;

    bool operator<(const Pair &other) const {
        return v > other.v;
    }
};

priority_queue<Pair> que;
const int N = 1000005;
long long a[N], b[N], c[N], n, count[N], m;

long long func(long long t, long long x) {
    return a[t] * x * x + b[t] * x + c[t];
}

int main() {
    cin >> n >> m;
    Pair tmp;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        tmp.num = i;
        tmp.v = func(i, 1);
        que.push(tmp);
        count[i] = 1;
    }
    while (m) {
        --m;
        tmp = que.top();
        que.pop();
        cout << tmp.v << ' ';
        tmp.v = func(tmp.num, ++count[tmp.num]);
        que.push(tmp);
    }
    return 0;
}