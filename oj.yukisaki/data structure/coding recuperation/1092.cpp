//
// Created by Libro on 2021/3/15.
//

#include <iostream>

using namespace std;

int a[2000005], n, head, tail, sum[2000005], ans, que[2000005];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    sum[0] = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }
    head = tail = ans = 0;
    for (int i = 1; i < 2 * n; ++i) {
        while (head < tail && sum[que[tail - 1]] > sum[i]) --tail;
        while (head < tail && que[head] + n <= i) ++head;
        que[tail++] = i;
        if (i >= n) {
            if (sum[que[head]] >= sum[i - n + 1]) ++ans;
        }
    }
    cout << ans << '\n';
}