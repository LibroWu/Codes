//
// Created by Libro on 2021/4/17.
//

#include <iostream>
#include <cstring>

using namespace std;

long long n, DP[35][35], root[35][35];

void dfs(int l, int r) {
    if (l > r) return;
    cout << root[l][r] << ' ';
    if (l == r) return;
    dfs(l, root[l][r] - 1);
    dfs(root[l][r] + 1, r);
}

int main() {
    cin >> n;
    memset(DP, 0, sizeof(DP));
    for (int i = 1; i <= n; ++i) {
        cin >> DP[i][i];
        root[i][i] = i;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= i - 1; ++j)
            DP[i][j] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= n - i + 1; ++j) {
            for (int k = j; k <= j + i - 1; ++k) {
                if (DP[j][k - 1] * DP[k + 1][j + i - 1] + DP[k][k] > DP[j][j + i - 1]) {
                    DP[j][j + i - 1] = DP[j][k - 1] * DP[k + 1][j + i - 1] + DP[k][k];
                    root[j][j + i - 1] = k;
                }
            }
        }
    }
    cout << DP[1][n] << '\n';
    dfs(1, n);
}