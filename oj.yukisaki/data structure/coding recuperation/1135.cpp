//
// Created by Libro on 2021/4/15.
//

#include <iostream>

using namespace std;
char tree1[30], tree2[30];
int l1[30], r1[30], l2[30], r2[30];
bool flag1[30] = {0}, flag2[30] = {0};

void read(int &tmp) {
    tmp = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') {
            tmp = -1;
            return;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        tmp = tmp * 10 + c - '0';
        c = getchar();
    }
}

bool check(int u, int v) {
    if (l1[u] == -1) swap(l1[u], r1[u]);
    if (l2[v] == -1) swap(l2[v], r2[v]);
    if (l1[u] == -1) return (l2[v] == -1);
    //1 not empty
    if (l2[v] == -1) return false;
    if (tree1[l1[u]] != tree2[l2[v]]) {
        swap(l2[v], r2[v]);
        if (l2[v] == -1) return false;
        if (tree2[l2[v]] != tree1[l1[u]]) return false;
    }
    if (r1[u] == -1) {
        if (!check(l1[u], l2[v])) return false;
        return (r2[v] == -1);
    }
    //1 has right child
    if (r2[v] == -1) return false;
    if (tree1[r1[u]] != tree2[r2[v]]) return false;
    if (!check(l1[u], l2[v])) return false;
    if (!check(r1[u], r2[v])) return false;
    return true;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tree1[i];
        if (tree1[i] >= 'a' && tree1[i] <= 'z') tree1[i] += 'A' - 'a';
        read(l1[i]);
        read(r1[i]);
        flag1[l1[i]] = 1;
        flag1[r1[i]] = 1;
    }
    int m;
    cin >> m;
    if (n == m) {
        for (int i = 0; i < m; ++i) {
            cin >> tree2[i];
            if (tree2[i] >= 'a' && tree2[i] <= 'z') tree2[i] += 'A' - 'a';
            read(l2[i]);
            read(r2[i]);
            flag2[l2[i]] = 1;
            flag2[r2[i]] = 1;
        }
        int i = 0, j = 0;
        for (; i < n; ++i)
            if (!flag1[i]) break;
        for (; j < n; ++j)
            if (!flag2[j]) break;
        if (i == n || j==n || tree1[i]!=tree2[j]) cout << "No\n";
        else
            cout << ((check(i, j)) ? "Yes" : "No") << '\n';
    } else cout << "No\n";
    return 0;
}