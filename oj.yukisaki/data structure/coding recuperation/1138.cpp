#include <iostream>

using namespace std;

const int N=100005;
const long long P=1000000007;
struct Edge{
    int next,vet;
} edge[2*N];

int Head[N]={0},tot=0,n;
long long ans[N],DP[N];

void build(int u,int v){
    edge[++tot].next=Head[u];
    edge[tot].vet=v;
    Head[u]=tot;
}

void dfs(int u,int pa) {
    DP[u]=1;
    int v;
    for (int i = Head[u]; i  ; i=edge[i].next) {
        v=edge[i].vet;
        if (v==pa) continue;
        dfs(v,u);
        DP[u]=DP[u]*(1+DP[v])%P;
    }
}

long long inverse(long long x){
    long long p=P-2;
    long long tmp=1;
    while (p) {
        if (p&1) tmp=tmp*x%P;
        p>>=1;
        x=x*x%P;
    }
    return tmp;
}

void dfss(int u,int pa,long long k) {
    ans[u]=DP[u]*k%P;
    int v;
    for (int i = Head[u]; i  ; i=edge[i].next) {
        v=edge[i].vet;
        if (v==pa) continue;
        k=k*(DP[v]+1)%P;
    }
    for (int i = Head[u]; i  ; i=edge[i].next) {
        v=edge[i].vet;
        if (v==pa) continue;
        dfss(v,u,(k*inverse(DP[v]+1)+1)%P);
    }
}

int main(){
    cin>>n;
    int x;
    for (int i = 2; i <= n; ++i) {
        cin>>x;
        build(i,x);
        build(x,i);
    }
    dfs(1,0);
    dfss(1,0,1);
    for (int i = 1; i <= n; ++i) {
        cout<<ans[i]<<' ';
    }
}