//Libro
//Mars Energy Neclace

#include <iostream>

using namespace std;
long long int a[205], dp[205][205] = {0};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i=0;i<n+n;++i)
        for (int j=i;j>=0;--j)
            for (int k=j;k<i;++k)
                dp[j][i]=max(dp[j][i],dp[j][k]+dp[k+1][i]+a[j]*a[k+1]*a[i+1]);
    long long int ans=0;
    for (int i = 0; i < n; ++i) ans = max(ans , dp[i][i+n-1]);
    cout<<ans;
}