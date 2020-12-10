//
// Created by LIBRO on 2020/11/19.
// creat virtual points

#include <iostream>
#include <map>
#include <queue>
using namespace std;
const int NN=3e5+5;
const int INF=1e8;
int n,m,a[NN],tot=0,tot_num=0;
map<int,int> trans;
int head[NN*2]={},dist[NN*2];
bool inque[NN*2]={};
struct Edge{
    int next,vet,cost;
}p[4*NN];

void build(int x,int y,int c){
    p[++tot]={head[x],y,c};
    head[x]=tot;
}

int main(){
    cin>>n;
    for (int i=0;i<n;++i){
        cin>>a[i];
        if (trans.count(a[i])==0){
            trans[a[i]]=++tot_num;
        }
    }
    for (int i=0;i<n;++i){
        if (i!=n-1) {
            build(i,i+1,2);
            build(i+1,i,2);
        }
        build(i,n+trans[a[i]],1);
        build(n+trans[a[i]],i,1);
    }
    for (int i=0;i<=n+tot_num;++i){
        dist[i]=INF;
    }
    queue<int> que;
    while (!que.empty())que.pop();
    que.push(0);
    inque[0]=1;
    dist[0]=0;
    int u,v,cost;
    while (!que.empty()){
        u=que.front();
        que.pop();
        inque[u]=0;
        for (int i=head[u];i;i=p[i].next){
            v=p[i].vet;cost=p[i].cost;
            if (dist[v]>dist[u]+cost){
                dist[v]=dist[u]+cost;
                if (!inque[v]){
                    inque[v]=1;
                    que.push(v);
                }
            }
        }
    }
    cout<<(dist[n-1]>>1)<<'\n';
}