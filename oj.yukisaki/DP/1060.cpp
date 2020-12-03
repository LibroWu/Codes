//Libro
//L-bots
#include <iostream>
#define ll long long
using namespace std;
long long int a[1005][1005],dp[1005][2];
int r,c;
long long int ans=0;

inline ll max(ll &a,ll& b){return ((a>b)?a:b);}

int main(){
    cin>>r>>c;
    for (int i=1;i<=r;++i)
        for (int j=1;j<=c;++j)
            cin>>a[i][j];
    for (int i=1;i<=r;++i){
        for (int j=0;j<=c;++j) dp[j][0]=dp[j][1]=0;
        for (int j=2;j<=c;++j) {
            dp[j][0]=max(dp[j-1][0],dp[j-1][1] );
            dp[j][1]=dp[j-1][0] + ((0>a[i][j]+a[i][j-1])?0:a[i][j]+a[i][j-1]);
        }
        ans+=max(dp[c][0],dp[c][1]);
    }
    for (int i=1;i<=c;++i){
        for (int j=0;j<=r;++j) dp[j][0]=dp[j][1]=0;
        for (int j=2;j<=r;++j) {
            dp[j][0]=max(dp[j-1][0],dp[j-1][1] );
            dp[j][1]=dp[j-1][0] + ((0>a[j][i]+a[j-1][i])?0:a[j][i]+a[j-1][i]);
        }
        ans+=max(dp[r][0],dp[r][1]);
    }
    cout<<ans;
}
