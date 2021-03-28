//
// Created by Libro on 2021/3/15.
//

#include <iostream>

using namespace std;

int n, m, a, h[1005][1005], row1[1005][1005], row2[1005][1005], h1, t1, h2, t2, que1[1005], que2[1005],ans=1000000005;

int main() {
    cin >> n >> m >> a;
    for (int i = 0; i < n; ++i) {
        h1 = t1 = h2 = t2 = 0;
        for (int j = 0; j < m; ++j) {
            cin >> h[i][j];
            //max
            while (h1 < t1 && h[i][que1[t1 - 1]] < h[i][j]) --t1;
            while (h1 < t1 && que1[h1] + a <= j) ++h1;
            que1[t1++] = j;
            //min
            while (h2 < t2 && h[i][que2[t2 - 1]] > h[i][j]) --t2;
            while (h2 < t2 && que2[h2] + a <= j) ++h2;
            que2[t2++] = j;
            if (j >= a - 1) {
                row1[i][j - a + 1] = h[i][que1[h1]];
                row2[i][j - a + 1] = h[i][que2[h2]];
            }
        }
    }
    for (int j = 0; j < m - a + 1; ++j) {
        t1 = t2 = h1 = h2 = 0;
        for (int i = 0; i < n; ++i) {
            //max
            while (h1 < t1 && row1[que1[t1 - 1]][j] < row1[i][j]) --t1;
            while (h1 < t1 && que1[h1] + a <= i) ++h1;
            que1[t1++] = i;
            //min
            while (h2 < t2 && row2[que2[t2 - 1]][j] > row2[i][j]) --t2;
            while (h2 < t2 && que2[h2] + a <= i) ++h2;
            que2[t2++] = i;
            if (i>=a-1) {
                ans=min(ans,row1[que1[h1]][j]-row2[que2[h2]][j]);
            }
        }
    }
    cout<<ans<<'\n';
}