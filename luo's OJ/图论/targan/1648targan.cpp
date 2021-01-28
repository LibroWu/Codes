//
// Created by lenovo on 2020/10/19.
//
  
#include<iostream>
  
using namespace std;
  
  
struct point{
    int next,vet;
};
  
int tot=0,bridge=0,dfn[100005]={},low[100005]={},head[100005]={},n,m,root,num=0;
point p[1000005];
bool cut[100005]={},st[100005]={};
  
inline int min(int x,int y){
    return ((x>y)?y:x);
}
  
void build(int s,int e){
    p[++tot].next=head[s];
    p[tot].vet=e;
    head[s]=tot;
}
  
void targan(int x,int fa){
    int v,son=0;
    bool ok = false;
    low[x]=dfn[x]=++num;
    st[x]=true;
    for (int i=head[x];i!=0;i=p[i].next){
        v=p[i].vet;
        if (v==fa && !ok) {
            ok=true;
            continue;
        }
        if (dfn[v]==0){
            son++;
            targan(v,x);
            if (low[v]>dfn[x]) bridge++;
            if (low[v]>=dfn[x])cut[x]=true;
            low[x]=min(low[v],low[x]);
        }
        else  low[x]=min(low[x],dfn[v]);
    }
    if (x==root)
        if (son>1) cut[x]=true; else cut[x]=false;
    st[x]=false;
}
  
int main(){
    cin>>n>>m;
    for (int i=0;i<m;++i){
        static int s,e;
        cin>>s>>e;
        build(s,e);
        build(e,s);
    }
    for (int i=1;i<=n;++i)
        if (dfn[i]==0) {
            root=i;
            targan(i,0);
        }
    int count=0;
    for (int i=1;i<=n;++i) if (cut[i]) count++;
    cout<<count<<' '<<bridge;
}