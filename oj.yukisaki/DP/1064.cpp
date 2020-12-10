//Libro
//the number of the submatrix whose sum%k=0

#include <iostream>

using namespace std;
int a[405][405]={0},sum[405][405]={0};
int n,m,p,key;
long long int ans=0;
int cnt[1000005]={};

int main(){
    cin>>n>>m>>p;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j){
            cin>>a[i][j];
            a[i][j]%=p;
            if (a[i][j]<0) a[i][j]+=p;
            sum[i][j]=(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j])%p;
            if (sum[i][j]<0) sum[i][j]+=p;
        }
    cnt[0]=1;
    for (int j=1;j<=m;++j) {
        for (int k = j; k <= m; ++k) {
            for (int i = 1; i <= n; ++i) {
                key = (sum[i][k] - sum[i][j - 1]);
                if (key < 0) key += p;
                ans += cnt[key];
                ++cnt[key];
            }
            for (int i = 1; i <= n; ++i) {
                key = (sum[i][k] - sum[i][j - 1]);
                if (key < 0) key += p;
                --cnt[key];
            }
        }
    }
    cout<<ans;
}