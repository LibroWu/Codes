//
// Created by libro on 2021/4/13.
//

#include <iostream>
#include <queue>

using namespace std;

const int N = 200005;
int n, m;
string s;
bool existed[N];
int Pre[N], Next[N], v[N];

struct Pair {
    int l, r;

    Pair() = default;

    Pair(int l, int r) : l(l), r(r) {}

    bool operator<(const Pair &other) const {
        if (abs(v[l] - v[r]) > abs(v[other.l] - v[other.r]) ||
            abs(v[l] - v[r]) == abs(v[other.l] - v[other.r]) && l > other.l)
            return true;
        return false;
    }
};

priority_queue<Pair> pq;
int num = 0;
Pair Ans[N];

int main() {
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        existed[i] = true;
        Pre[i] = i - 1;
        Next[i] = i + 1;
        if (i && s[i - 1] != s[i]) pq.push(Pair(i - 1, i));
    }
    Pre[0] = 0;
    Next[n - 1] = n - 1;
    while (!pq.empty()) {
        Pair tmp = pq.top();
        pq.pop();
        if (existed[tmp.l] && existed[tmp.r]) {
            Ans[num++] = tmp;
            existed[tmp.l] = false;
            existed[tmp.r] = false;
            if (existed[Pre[tmp.l]] && existed[Next[tmp.l]] && s[Pre[tmp.l]] != s[Next[tmp.l]])
                pq.push(Pair(Pre[tmp.l], Next[tmp.l]));
            Pre[Next[tmp.l]] = Pre[tmp.l];
            Next[Pre[tmp.l]] = Next[tmp.l];
            if (existed[Pre[tmp.r]] && existed[Next[tmp.r]] && s[Pre[tmp.r]] != s[Next[tmp.r]])
                pq.push(Pair(Pre[tmp.r], Next[tmp.r]));
            Pre[Next[tmp.r]] = Pre[tmp.r];
            Next[Pre[tmp.r]] = Next[tmp.r];
        }
    }
    cout << num << '\n';
    for (int i = 0; i < num; ++i) {
        cout << Ans[i].l + 1 << ' ' << Ans[i].r + 1 << '\n';
    }
}