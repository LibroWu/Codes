//
// Created by libro on 2020/11/5.
//多维体相邻块

#include <iostream>

using namespace std;

int n,m,multi=1,a[100005],color[262150],father[262150],cnt=0,sum[100005],visited[262150],u,v;

int getfather(int x){
    if (father[x]==x) return x;
    father[x]=getfather(father[x]);
    return father[x];
}

int main(){
    cin>>n;
    cnt=-1;
    for (int i=0;i<n;++i) cin>>a[i];
    for (int i=n-1;i>=0;--i)
    {
        sum[++cnt]=multi;
        multi*=a[i];
        if (a[i]==1) cnt--;
    }
    sum[cnt+1]=multi;
    for (int i=0;i<multi;++i){
        cin>>color[i];
        father[i]=i;
        visited[i]=0;
    }
    int ans=multi;
    for (int i=0;i<multi;++i){
        for (int j=0;j<=cnt;++j)
            if ((i+sum[j])/sum[j+1]==i/sum[j+1] && color[i+sum[j]]==color[i]){
                u=getfather(i);
                v=getfather(i+sum[j]);
                if (u!=v) {
                    father[u]=v;
                    ans--;
                }
            }
    }
    cout<<ans<<'\n';
}