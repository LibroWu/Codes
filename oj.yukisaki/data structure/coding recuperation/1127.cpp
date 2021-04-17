//
// Created by libro on 2021/4/11.
//

#include <iostream>
#include <cstring>

using namespace std;

int n, m, tot = 0;
int trie[1000005][3], End[1000005];
string s;
bool ans;

void build(const string &s) {
    int ptr = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (trie[ptr][s[i] - 'a'] == 0) {
            trie[ptr][s[i] - 'a'] = ++tot;
            ptr = trie[ptr][s[i] - 'a'];
        } else ptr = trie[ptr][s[i] - 'a'];
    }
    ++End[ptr];
}

void dfs(int ptr, int t, bool flag) {
    if (ans) return;
    if (t == s.length() && End[ptr]) {
        if (flag) ans = flag;
        return;
    }
    if (trie[ptr][s[t] - 'a']) dfs(trie[ptr][s[t] - 'a'], t + 1, flag);
    if (!flag)
        for (int i = 0; i < 3; ++i)
            if (i != s[t] - 'a')
                if (trie[ptr][i]) dfs(trie[ptr][i], t + 1, true);
}

int main() {
    memset(trie, 0, sizeof(trie));
    memset(End, 0, sizeof(End));
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        build(s);
    }
    for (int i = 0; i < m; ++i) {
        cin >> s;
        ans = false;
        dfs(0, 0, 0);
        cout << ((ans) ? "YES\n" : "NO\n");
    }
}