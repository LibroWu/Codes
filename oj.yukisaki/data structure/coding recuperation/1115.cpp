//
// Created by Libro on 2021/3/31.
//

#include <iostream>
#include <cstring>
using namespace std;

int n,W;

struct Edge{
    int next,v;
} edge[2005];

int Head[2005],tot=0,p[2005],v[2005],w[2005],ans[2005];

inline int max(int a,int b){
    return ((a>b)?a:b);
}

inline void build(int u,int v){
    edge[++tot].next=Head[u];
    edge[tot].v=v;
    Head[u]=tot;
}

void dfs(int u,int sum_W) {
    for (int i = Head[u]; i ; i=edge[i].next) {
        int vet=edge[i].v;
        for (int j = W; j >= sum_W+w[vet] ; --j) {
            ans[j]=max(ans[j],ans[j-w[vet]]+v[vet]);
        }
        dfs(vet,sum_W+w[vet]);
    }
}

int main(){
    memset(ans,0,sizeof(ans));
    memset(Head,0,sizeof(Head));
    cin>>n>>W;
    p[0]=v[0]=w[0]=0;
    for (int i = 1; i <= n; ++i) {
        cin>>p[i]>>w[i]>>v[i];
        build(p[i],i);
    }
    dfs(0,0);
    int Ans=0;
    for (int i = 0; i <= W; ++i) {
        Ans=max(Ans,ans[i]);
    }
    cout<<Ans;
}