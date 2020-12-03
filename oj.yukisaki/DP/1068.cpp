//
// Created by Libro on 2020/12/3.
//pass the message

//Libro

#include <iostream>

using namespace std;
int n, m, a[55][55], dp[55][55][55][55] = {};

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> a[i][j];
    for (int x1 = 0; x1 < n; ++x1)
        for (int y1 = 0; y1 < m; ++y1)
            for (int x2 = 0; x2 < n; ++x2)
                for (int y2 = 0; y2 < m; ++y2)
                    if (x2 <= x1 && y2 >= y1) continue;
                    else {
                        if (x1>0 && x2>0) dp[x1][y1][x2][y2]=max(dp[x1][y1][x2][y2],dp[x1-1][y1][x2-1][y2]+a[x1][y1]+a[x2][y2]);
                        if (x1>0 && y2>0) dp[x1][y1][x2][y2]=max(dp[x1][y1][x2][y2],dp[x1-1][y1][x2][y2-1]+a[x1][y1]+a[x2][y2]);
                        if (y1>0 && x2>0) dp[x1][y1][x2][y2]=max(dp[x1][y1][x2][y2],dp[x1][y1-1][x2-1][y2]+a[x1][y1]+a[x2][y2]);
                        if (y1>0 && y2>0) dp[x1][y1][x2][y2]=max(dp[x1][y1][x2][y2],dp[x1][y1-1][x2][y2-1]+a[x1][y1]+a[x2][y2]);
                    }
    cout<<dp[n-2][m-1][n-1][m-2];
}