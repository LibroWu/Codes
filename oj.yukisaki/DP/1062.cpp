//
// Created by Libro on 2020/12/3.
// bags

//Libro

#include <iostream>

using namespace std;
int a[1005]={};

inline int max(int a,int b){
    return ((a>b)?a:b);
}

int main() {
    int n, m, p, w, v, sum, d, value, cost;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> p >> w >> v;
        sum = 0;
        d = 1;
        while (sum + d <= p) {
            sum += d;
            value = v * d;
            cost = w * d;
            for (int j = m; j >= cost; --j)
                a[j] = max(a[j], a[j - cost] + value);
            d <<= 1;
        }
        d = p - sum;
        value = v * d;
        cost = w * d;
        for (int j = m; j >= cost; --j)
            a[j] = max(a[j], a[j - cost] + value);
    }
    int ans = 0;
    for (int i = 0; i <= m; ++i) ans = max(ans, a[i]);
    cout << ans;
}