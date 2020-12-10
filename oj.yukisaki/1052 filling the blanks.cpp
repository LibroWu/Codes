//dfs dp and graph
#include <iostream>
#include <queue>
//#define Libro_debug1
using namespace std;
const int NN=3e6;
const int INF=1e8;
struct Edge{
    int vet,next,cost;
}p[NN<<5];
struct point{
    int node,dist;
    bool operator<(const point & other) const{ return dist<other.dist;}
};

int n,m,a[8][8],_plus[8];
int tot=0,tot_num=0,head[40005]={0},trans[8][NN]={0};
bool b[8][8]={0};
int dist[40005];
void build(int a,int b,int c,int x){
    if (trans[x][a]==0) trans[x][a]=++tot_num;
    if (trans[x-1][b]==0) trans[x-1][b]=++tot_num;
    int v=trans[x][a];
    int u=trans[x-1][b];
    p[++tot]={v,head[u],-c};
    head[u]=tot;
}

void dfss(int step,int x){
    if (step==m+1){
        int sum=0,Hash=0,Hash0=0;
#ifdef Libro_debug
        cout<<"***row="<<x-1<<"***\n";
#endif
        for (int i=1;i<=m;++i) {
            sum+=i*a[x][i];
            Hash+=a[x][i]*_plus[i];
            Hash0+=a[x-1][i]*_plus[i];
#ifdef Libro_debug
            cout<<a[x-1][i]<<' ';
#endif
        }
#ifdef Libro_debug
        cout<<'\n';
        for (int i=1;i<=m;++i) cout<<a[x][i]<<' ';
        cout<<"\n***end***\n";
#endif
        build(Hash,Hash0,sum,x);
    }
    if (a[x][step]!=0) dfss(step+1,x);
    else
        for (int i=1;i<=m;++i)
            if (!b[x][i] && (step==1 || abs(i-a[x][step-1])!=1) && abs(a[x-1][step]-i)!=1 && (step==m || a[x][step+1]==0 || abs(a[x][step+1]-i)!=1)){
                b[x][i]=1;
                a[x][step]=i;
                dfss(step+1,x);
                b[x][i]=0;
                a[x][step]=0;
            }
}

void dfs(int step,int x){
    if (step==m+1){
        if (x==1){
            int sum=0,Hash=0;
            for (int i=1;i<=m;++i) {
                sum+=i*a[x][i];
                Hash+=a[x][i]*_plus[i];
            }
            build(Hash,0,sum,x);
        }
        dfss(1,x+1);
    }
    if (a[x][step]!=0) dfs(step+1,x);
    else
        for (int i=1;i<=m;++i)
            if (!b[x][i] && (step==1 || abs(i-a[x][step-1])!=1) && (a[x+1][step]==0||abs(a[x+1][step]-i)!=1) && (step==m || a[x][step+1]==0 || abs(a[x][step+1]-i)!=1)){
                b[x][i]=1;
                a[x][step]=i;
                dfs(step+1,x);
                b[x][i]=0;
                a[x][step]=0;
            }
}


int main(){
    cin>>n>>m;
    _plus[1]=1;
    for (int i=2;i<=m;++i) _plus[i]=_plus[i-1]<<3;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j){
            cin>>a[i][j];
            b[i][a[i][j]]=1;
        }
    for (int i=1;i<n;++i){
        dfs(1,i);
    }

    //dijkstra
    for (int i=0;i<=tot_num;++i) dist[i]=INF;
    dist[trans[0][0]]=0;
    priority_queue<point> que;
    point tmp;
    int u,v;
    while (!que.empty()) que.pop();
    que.push({trans[0][0],0});
    while (!que.empty()){
        tmp=que.top();
        que.pop();
        if (tmp.dist!=dist[tmp.node]) continue;
        u=tmp.node;
        for (int i=head[u];i;i=p[i].next){
            v=p[i].vet;
            if (dist[v]>dist[u]+p[i].cost){
                dist[v]=dist[u]+p[i].cost;
                que.push({v,dist[v]});
            }
        }
    }
    int ans=0;
    for (int i=0;i<=NN;++i)
        if (trans[n][i]!=0 && dist[trans[n][i]]<ans) ans=dist[trans[n][i]];
    cout<<-ans<<'\n';
#ifdef Libro_debug1
    cout<<trans[0][0]<<' '<<tot_num<<' '<<tot;
#endif
    return 0;
}