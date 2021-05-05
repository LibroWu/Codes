//
// Created by Libro on 2021/4/27.
//

#include <iostream>

using namespace std;
const long long P1 = 1e9 + 7;
const long long key1 = 131;
const long long P2 = 1000000033;
const long long key2 = 113;
const long long P3 = 1000000093;
const long long key3 = 193;

long long HASH1[1000005][2], HASH2[1000005][2], HASH3[1000005][2];
long long a[1000005];
int n, m, l[1000005], r[1000005], num[1000005], ans;

void dfs(int u) {
    num[u] = 1;
    HASH1[u][0] = HASH1[u][1] = a[u];
    HASH2[u][0] = HASH2[u][1] = a[u];
    if (l[u]) dfs(l[u]);
    if (r[u]) dfs(r[u]);
    num[u] += num[l[u]] + num[r[u]];
    HASH1[u][0] = (HASH1[u][0]*num[u] + HASH1[l[u]][0] * key1 * key1 + HASH1[r[u]][0] * key1*key3) % P1;
    HASH1[u][1] = (HASH1[u][1]*num[u] + HASH1[r[u]][1] * key1 * key1 + HASH1[l[u]][1] * key1*key3) % P1;
    HASH2[u][0] = (HASH2[u][0]*num[u]*num[u] + HASH2[l[u]][0] * key2 * key2*key1 + HASH2[r[u]][0] * key2) % P2;
    HASH2[u][1] = (HASH2[u][1]*num[u]*num[u] + HASH2[r[u]][1] * key2 * key2*key1 + HASH2[l[u]][1] * key2) % P2;
    HASH3[u][0] = (HASH3[u][0]*u*u + HASH3[l[u]][0] * key3 * key3 + HASH3[r[u]][0] * key3) % P3;
    HASH3[u][1] = (HASH3[u][1]*u*u + HASH3[r[u]][1] * key3 * key3 + HASH3[l[u]][1] * key3) % P3;
    if (HASH1[l[u]][0] == HASH1[r[u]][1] && HASH2[l[u]][0] == HASH2[r[u]][1] && HASH3[l[u]][0] == HASH3[r[u]][1])
        if (num[u] > ans) ans = num[u];
}

int main() {
    cin >> n;
    num[0] = 0;
    HASH1[0][0] = HASH1[0][1] = n;
    HASH2[0][0] = HASH2[0][1] = n>>1;
    HASH3[0][0] = HASH3[0][1] = n>>2;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
        if (l[i] == -1) l[i] = 0;
        if (r[i] == -1) r[i] = 0;
    }
    dfs(1);
    cout << ans;
}