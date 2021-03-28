//
// Created by Libro on 2021/3/15.
//

#include <iostream>
#include <cstring>

using namespace std;

int n, m, a[1005], x, q[1005], head, tail, ans = 0;

int main() {
    memset(a, 0, sizeof(0));
    cin >> m >> n;
    head = tail = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (a[x] == 0) {
            ++ans;
            a[x] = 1;
            q[tail++] = x;
            if (tail - head > m) {
                a[q[head]] = 0;
                ++head;
            }
        }
    }
    cout << ans;
    return 0;
}