// Created by lenovo on 2020/10/22.
//

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e7 + 1e2;
int a[maxn], l[maxn], r[maxn], n, m, q, L ,k;

struct block{
    long long int *sum1,*sum2;
    void init(int x){
        sum1=new long long int [x+2];
        sum2=new long long int [x+2];
    }
    void close(){
        delete [] sum1;
        delete [] sum2;
    }
};

unsigned int seed;
unsigned int xorshift() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
void generator() {
    for (int i = 1; i <= n; ++i)
        a[i] = xorshift() >> 1u;
    for (int i = 1; i <= q; ++i)
        r[i] = (l[i] = xorshift() % (n - L + 1) + 1) + L - 1;
}

int main() {
    cin >> n >> m >> q >> L >> seed;
    generator();
    //todo
    k=n/L;
    if (! (n%L==0))k++;
    block* p= new block[k];
    //prepare;
    for (int i=0;i<k;++i){
        static int v;
        p[i].init(L);
        p[i].sum2[L+1]=p[i].sum1[0]=1;
        for (int j=1;j<=L;++j){
            v=i*L+j;
            if (v>n) a[v]=1;
            p[i].sum1[j]=p[i].sum1[j-1]*a[v]%m;
        }
        for (int j=L;j>=1;--j){
            v=i*L+j;
            if (v>n) a[v]=1;
            p[i].sum2[j]=p[i].sum2[j+1]*a[v]%m;
        }
    }
    //work
    for (int i=1;i<=q;++i){
        if (l[i]%L==1) printf("%d\n",p[l[i]/L].sum1[L]);
        else printf("%d\n",p[(l[i]-1)/L].sum2[(l[i]-1)%L+1]*p[(l[i]-1)/L+1].sum1[(l[i]-1)%L]%m);
    }

    for (int i=0;i<k;++i) p[i].close();
    delete [] p;
    return 0;
}