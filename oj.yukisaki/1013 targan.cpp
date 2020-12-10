#include<iostream>
#include<algorithm>
using namespace std;

//new graph
struct edge{
    int e,s,cost;
};

struct point{
    int next,vet,cost1,cost2,s;
    bool isbridge=false;
};

int edgenum=0,tot=0,bridge=0,father[100005],dfn[100005]={},low[100005]={},head[100005]={},n,m,root,num=0;
point p[1000005];
bool cut[100005]={},st[100005]={};
edge a[1000005];
inline int min(int x,int y){
    return ((x>y)?y:x);
}

int getfaher(int v){
    if (father[v]==v) return v;
    father[v]=getfaher(father[v]);
    return father[v];
}

void build(int s,int e,int a,int b){
    p[++tot].next=head[s];
    p[tot].s=s;
    p[tot].vet=e;
    p[tot].cost1=a;
    p[tot].cost2=b;
    head[s]=tot;
}

//get the pair of edges
int ff(int x){
    if (x&1) return x+1;
    return x-1;
}

void add(int s,int e,int c){
    a[++edgenum].s=s;
    a[edgenum].e=e;
    a[edgenum].cost=c;
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
            if (low[v]>dfn[x]) {bridge++;p[i].isbridge=1;p[ff(i)].isbridge=1;}
            if (low[v]>=dfn[x])cut[x]=true;
            low[x]=min(low[v],low[x]);
        }
        else low[x]=min(low[x],dfn[v]);
    }
    if (x==root)
        if (son>1) cut[x]=true; else cut[x]=false;
    st[x]=false;
}

int main(){
    cin>>n>>m;
    for (int i=0;i<m;++i){
        static int s,e,a,b;
        cin>>s>>e>>a>>b;
        build(s,e,a,b);
        build(e,s,a,b);
    }
    for (int i=1;i<=n;++i)
        if (dfn[i]==0) {
            root=i;
            targan(i,0);
        }
    //Kruskal
    for (int i=1;i<=2*m;i+=2)
        if (p[i].isbridge) {add(p[i].s,p[i].vet,p[i].cost2);}
        else add(p[i].s,p[i].vet,p[i].cost1);
    sort(a+1,a+edgenum+1,[](edge &x,edge &y){return x.cost<y.cost;});
    for (int i=1;i<=n;++i) father[i]=i;
    int cnt=0,i=1,u,v;
    long long int ans=0;
    while (cnt<n-1){
        u=getfaher(a[i].s);
        v=getfaher(a[i].e);
        if (u!=v) {
            father[u]=v;
            ans+=a[i].cost;
            cnt++;
        }
        i++;
    }
    cout<<ans;
}