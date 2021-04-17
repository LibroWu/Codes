//
// Created by Libro on 2021/4/12.
//

#include <iostream>

using namespace std;

const unsigned int P1 = 9998861;

unsigned int getHash(const string &s) {
    unsigned int tmp = 0;
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        tmp = (tmp << 7) + s[i] + s[i] * s[i];
        tmp %= P1;
    }
    return tmp;
}

bool in_dictionary[P1] = {0};
int existed[P1] = {0};
int n, m, num = 0;
string s;
int que[100005];
unsigned int k[100005];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        unsigned int K = getHash(s);
        if (!in_dictionary[K]) {
            ++num;
            in_dictionary[K] = 1;
        }
    }
    cin >> m;
    bool flag;
    int sum = 0, l = 0, r = 0, ans = m;
    for (int i = 0; i < m; ++i) {
        flag = false;
        cin >> s;
        k[i] = getHash(s);
        if (in_dictionary[k[i]]) {
            if (existed[k[i]] == 0) {
                flag = true;
                ++sum;
            }
            ++existed[k[i]];
        }
        que[r++] = i;
        while (l < r && (!in_dictionary[k[que[l]]] || existed[k[que[l]]] > 1)) {
            if (existed[k[que[l]]] > 1) --existed[k[que[l]]];
            ++l;
        }
        if (flag) ans = r - l;
        else ans = min(ans, r - l);
    }
    cout << sum << '\n' << ans;
}