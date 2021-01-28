#include <cstdio>
using namespace std;
 
 
const int NN=20;
int n,m,tot;
int head[100005]={0},depth[100005]={0},father[100005][NN]={0};
int dist[100005]={0};
int Next[200005],vet[200005],cost[200005];
 
void build(int x,int y,int c){
    Next[++tot]=head[x];
    head[x]=tot;
    cost[tot]=c;
    vet[tot]=y;
    return;
}
 
void prepare(int u,int fa){
    for (int i=1;i<NN-1;++i){
        father[u][i]=father[father[u][i-1]][i-1];
    }
    for (int i=head[u];i!=0;i=Next[i]){
        static int v;
        v=vet[i];
        if (v==fa) continue;
        father[v][0]=u;
        dist[v]=dist[u]+cost[i];
        depth[v]=depth[u]+1;
        prepare(v,u);
    }
    return;
}
 
int lca(int x,int y){
    if (depth[x]<depth[y]) {
        int tmp=x;x=y;y=tmp;
    }
    for (int i=NN-1;i>=0;--i){
        if (depth[father[x][i]]>=depth[y])
            x=father[x][i];
            if (x==y) return x;
        }
    for (int i=NN-1;i>=0;--i)
        if (father[x][i]!=father[y][i]){
            x=father[x][i];
            y=father[y][i];
        }
    return father[x][0];
}
 
int main() {
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;++i) {
        static int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        build(a,b,c);
        build(b,a,c);
    }
    depth[1]=1;
    prepare(1,0);
    scanf("%d",&m);
    for (;m;--m){
        static int x,y,z;
        scanf("%d%d",&x,&y);
        z=lca(x,y);
        printf("%d\n",dist[x]+dist[y]-2*dist[z]);
    }
    return 0;
}