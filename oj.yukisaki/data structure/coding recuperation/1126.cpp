//
// Created by libro on 2021/4/12.
//

#include <iostream>

using namespace std;

class Heap {
private:
    void swap(long long &a, long long &b) {
        a = a ^ b, b = a ^ b, a = a ^ b;
    }

public:
    long long top, p[1000005];

    Heap() : top(0) {}

    void push(long long x) {
        p[++top] = x;
        long long child = top;
        while (child > 1) {
            if (p[child >> 1] > p[child]) {
                swap(p[child], p[child >> 1]);
                child = child >> 1;
            } else break;
        }
    }

    long long front() {
        return p[1];
    }

    bool empty() {
        return top;
    }

    void pop() {
        p[1] = p[top--];
        long long pa = 1, child;
        while (pa << 1 <= top) {
            if (((pa << 1 | 1) > top) || p[pa << 1] < p[pa << 1 | 1]) child = pa << 1;
            else child = pa << 1 | 1;
            if (p[pa] > p[child]) {
                swap(p[pa], p[child]);
                pa = child;
            } else break;
        }
    }
} h;

int n, m;

int main() {
    cin >> n >> m;
    int t = n - (n - m) % (m - 1) + m - 1;
    for (int i = 0; i < (t - n) % (m - 1); ++i) {
        h.push(0);
    }
    long long x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        h.push(x);
    }
    long long ans = 0, sum = 0;
    while (h.top > 1) {
        sum = 0;
        for (int i = 0; i < m; ++i) {
            sum += h.front();
            h.pop();
        }
        h.push(sum);
        ans += sum;
    }
    cout << ans << '\n';
}