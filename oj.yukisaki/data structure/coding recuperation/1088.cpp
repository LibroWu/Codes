//1088
#include <iostream>
#include <cstring>

using namespace std;

struct BIT {
    int t[100005], threshold;

    BIT(int n) : threshold(n) {
        memset(t, 0, sizeof(t));
    }

    inline int lowbit(int x) {
        return x & (-x);
    }

    void add(int x, int k) {
        while (x <= threshold) {
            t[x] += k;
            x += lowbit(x);
        }
    }

    int get(int x) {
        int tmp = 0;
        while (x) {
            tmp += t[x];
            x -= lowbit(x);
        }
        return tmp;
    }
};

int n, m;

int Find(int x, BIT &t) {
    int l = 1, r = n, mid, ttt;
    while (l < r) {
        mid = (l + r) >> 1;
        if ((ttt = t.get(mid)) < x)
            l = mid + 1;
        else
            r = mid;
    }
    return r;
}

int main() {
    cin >> n >> m;
    BIT t(n);
    for (int i = 1; i <= n; ++i) t.add(i, 1);

    int kk = 1, num = n, mm, k;
    bool dir = 0;
    while (num>1) {
        k = num * 2 - 2;
        mm = (m-1) % k;
        while (mm) {
            if (!dir) {
                if (kk + mm < num) {
                    kk = kk + mm;
                    mm = 0;
                }
                else {
                    mm -= num - kk;
                    kk = num;
                    dir = 1;
                }
            }
            else {
                if (kk - mm > 1) {
                    kk = kk - mm;
                    mm = 0;
                }
                else {
                    mm -= kk - 1;
                    kk = 1;
                    dir=0;
                }
            }
        }
        t.add(Find(kk, t), -1);
        --num;
        if (!dir) {
            if (kk == num) {
                dir = 1;
            }
        }
        else {
            --kk;
            if (kk == 1) dir = 0;
        }
    }
    cout << Find(1, t);

}