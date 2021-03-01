//RMQ based on BIT
//O((logN)^2) for each query 
#include <iostream>
#include <cstring>

using namespace std;

struct BIT_min {
    int data[50005], origin[50005];
    int num;

    BIT_min(int n) : num(n) {
        for (int i=1;i<=n;++i) data[i]=1000000000;
    }

    inline int lowbit(int x) {
        return x & (-x);
    }

    void change(int x, int y) {
        origin[x] = y;
        while (x <= num) {
            data[x] = min(data[x], y);
            x += lowbit(x);
        }
    }

    int query(int l, int r) {
        int tmp = 1000000000;
        while (l <= r) {
            while (r && r - lowbit(r) + 1 >= l) {
                tmp = min(tmp, data[r]);
                r -= lowbit(r);
            }
            if (l <= r) {
                tmp = min(tmp, origin[r]);
                --r;
            }
        }
        return tmp;
    }
};

struct BIT_max {
    int data[50005], origin[50005];
    int num;

    BIT_max(int n) : num(n) {
        memset(data, 0, sizeof(data));
    }

    inline int lowbit(int x) {
        return x & (-x);
    }

    void change(int x, int y) {
        origin[x] = y;
        while (x <= num) {
            data[x] = max(data[x], y);
            x += lowbit(x);
        }
    }

    int query(int l, int r) {
        int tmp = -1;
        while (l <= r) {
            while (r && r - lowbit(r) + 1 >= l) {
                tmp = max(tmp, data[r]);
                r -= lowbit(r);
            }
            if (l <= r) {
                tmp = max(tmp, origin[r]);
                --r;
            }
        }
        return tmp;
    }
};

int main() {
    int n, m, x, y;
    cin >> n >> m;
    BIT_max t_max(n);
    BIT_min t_min(n);
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        t_max.change(i, x);
        t_min.change(i, x);
    }
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        cout << t_max.query(x, y) - t_min.query(x, y) << '\n';
    }
}