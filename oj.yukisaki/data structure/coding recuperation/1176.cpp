//
// Created by Libro on 2021/5/10.
//

#include <iostream>

using namespace std;

int n, T[200005], dfn = 0, DFN[200005] = {0}, ans = 200005;
bool flag[200005];

void dfs(int x) {
    DFN[x] = ++dfn;
    flag[x] = true;
    if (!DFN[T[x]]) dfs(T[x]);
    else if (flag[T[x]]) ans = min(ans, DFN[x] - DFN[T[x]]);
    flag[x] = false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> T[i];
        flag[i] = false;
    }
    for (int i = 1; i <= n; ++i)
        if (!DFN[i])
            dfs(i);
    cout << ans + 1;
}