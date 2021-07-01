#include<iostream>
#include <cstring>

using namespace std;

int Head[100005], parent[100005][20],depth[100005],count[100005];
struct Edge {
    int next, vet;
} edge[700000];
int n, m, tot = 0;
long long ans=0;

void build(int u, int v) {
    edge[++tot] = Edge({Head[u], v});
    Head[u] = tot;
}

void prepare(int u, int pa) {
    parent[u][0]=pa;
    for (int i = 0; i < 19; ++i)
        parent[u][i+1]=parent[parent[u][i]][i];
    depth[u]=depth[pa]+1;
    for (int i = Head[u];  i ; i=edge[i].next) {
        int v=edge[i].vet;
        if (v==pa) continue;
        prepare(v,u);
    }
}
void swap(int& a,int &b){
    int c=a;
    a=b,b=c;
}
int lca(int u,int v){
    if (depth[u]<depth[v]) swap(u,v);
    for (int i = 19; i >=0 ; --i)
    if (depth[parent[u][i]]>=depth[v])u=parent[u][i];
    if (u==v) return u;
    for (int i = 19; i >=0 ; --i)
        if (parent[u][i]!=parent[v][i])u=parent[u][i],v=parent[v][i];
    return parent[u][0];
}

void dfs(int u, int pa) {
    for (int i = Head[u];  i ; i=edge[i].next) {
        int v=edge[i].vet;
        if (v==pa) continue;
        dfs(v,u);
        count[u]+=count[v];
    }
    if (count[u]==1) ans+=1;
    if (count[u]==0) ans+=m;
}

int main() {
    memset(count, 0, sizeof(count));
    memset(Head, 0, sizeof(Head));
    cin >> n >> m;
    int u, v;
    for (int i = 0; i < n-1; ++i) {
        cin >> u >> v;
        build(u, v);
        build(v, u);
    }
    for (int j = 0; j < 20; ++j) parent[0][j] = 0;
    prepare(1, 0);
    for (int i = 0; i < m; ++i) {
        cin>>u>>v;
        ++count[u];
        ++count[v];
        count[lca(u,v)]-=2;
    }
    dfs(1,0);
    cout<<ans-m;
}