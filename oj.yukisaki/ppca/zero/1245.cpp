#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const long long P=1000000007;
long long int B[200005],C[200005], n, x, y,p[200005];
struct Node{
    long long a;
    int num;
} A[200005];

int lowbit(int x){
    return x&(-x);
}

void modify(int x,int k){
    while (x<=n) {
        p[x]+=k;
        x+=lowbit(x);
    }
}
int get(int x){
    int res=0;
    while (x){
        res+=p[x];
        x-=lowbit(x);
    }
    return res;
}

int main() {
    memset(B,0, sizeof(B));
    memset(C,0, sizeof(C));
    memset(p,0, sizeof(p));
    cin >> n >> x >> y;
    for (int i = 1; i <= n; ++i) {
        cin >> A[i].a;
        A[i].num=i;
    }
    sort(A+1,A+n+1,[](const Node&a,const Node&b)->bool { return a.a<b.a;});
    int ptr=1,lptr=1,rptr=1;
    long long l_bound,r_bound;
    while (ptr<=n) {
        l_bound=A[ptr].a-x;
        r_bound=A[ptr].a+x;
        while (rptr<=n && A[rptr].a<=r_bound) {
            modify(A[rptr].num,1);
            ++rptr;
        }
        while (lptr<=ptr && A[lptr].a<l_bound) {
            modify(A[lptr].num,-1);
            ++lptr;
        }
        B[A[ptr].num]+=get(A[ptr].num-1);
        ++ptr;
    }
    memset(p,0, sizeof(p));
    ptr=1,lptr=1,rptr=1;
    while (ptr<=n) {
        l_bound=A[ptr].a-y;
        r_bound=A[ptr].a+y;
        while (rptr<=n && A[rptr].a<=r_bound) {
            modify(A[rptr].num,1);
            ++rptr;
        }
        while (lptr<=ptr && A[lptr].a<l_bound) {
            modify(A[lptr].num,-1);
            ++lptr;
        }
        C[A[ptr].num]+=get(n)-get(A[ptr].num);
        ++ptr;
    }
    long long ans=0;
    for (int i = 0; i < n; ++i) {
        ans+=B[i]*C[i]%P;
        ans%=P;
    }
    cout<<ans;
    return 0;
}