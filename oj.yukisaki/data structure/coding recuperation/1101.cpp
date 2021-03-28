//
// Created by Libro on 2021/3/18.
//

#include <iostream>

using namespace std;

#define LL long long
const int N=1000005;

LL a,b,c,x[N],sum[N],n,f[N];

class Monotonous_Stack{
public:
    int head,tail,que[N];

    Monotonous_Stack():head(0),tail(0){}

    inline LL Y(int i){
        return f[i]+a*sum[i]*sum[i]-b*sum[i];
    }

    //return k12<k23
    inline bool cmp(int j1,int j2,int j3){
        return ((Y(j1)-Y(j2))*(sum[j2]-sum[j3])-(Y(j2)-Y(j3))*(sum[j1]-sum[j2])>0);
    }
    void push_back(int i){
        if (tail-head<2) {
            que[tail++]=i;
            return;
        }
        while (tail-head>=2 && cmp(i,que[tail-1],que[tail-2])) --tail;
        que[tail++]=i;
    }

    //return kij>k
    //i should be less than j
    inline bool cmp2(int i,int j,LL k){
        return (k*(sum[j]-sum[i])-Y(j)+Y(i)<0);
    }

    int get(LL k){
        int l=0,r=tail-1,mid;
        while (l<r) {
            mid=(l+r)>>1;
            if (cmp2(que[mid],que[mid+1],k)) l=mid+1;
            else r=mid;
        }
        return que[l];
    };
};

Monotonous_Stack Monday;

int main(){
    cin>>n>>a>>b>>c;
    sum[0]=0;
    for (int i = 1; i <= n; ++i) {
        cin>>x[i];
        sum[i]=sum[i-1]+x[i];
    }
    f[0]=0;
    Monday.push_back(0);
    for (int i = 1; i <= n; ++i) {
        int t=Monday.get(2*a*sum[i]);
        f[i]=f[t]+a*(sum[i]-sum[t])*(sum[i]-sum[t])+b*(sum[i]-sum[t])+c;
        Monday.push_back(i);
    }
    cout<<f[n];
}