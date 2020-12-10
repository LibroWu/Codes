//
// Created by libro on 2020/11/2.
//

#include <iostream>

using namespace std;

long long int a[15][15],ans=0;
int n,m;
bool b[15]={0};
void dfs(int step,long long int reserve,long long int now){
    if (step==n+1) {
        if (reserve & 1) ans-=now;
            else ans+=now;
        return;
    }
    long long int cnt=0;
    for (int i=1;i<=n;++i)
        if (!b[i]){
        b[i]=1;
        dfs(step+1,reserve+step-cnt-1,now*a[step][i]);
        b[i]=0;
    }else cnt++;
    return;
}

int main(){
    cin>>n;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j) cin>>a[i][j];
    dfs(1,0,1);
    cout<<ans;
    return 0;
}