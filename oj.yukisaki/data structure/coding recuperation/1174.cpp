//
// Created by Libro on 2021/5/10.
//
#include <cstdio>
using namespace std;

long long n,a[1000005],b[1000005],m;

void mergeSort(int l,int r,long long *a) {
    if (l==r) return;
    int mid=l+r>>1;
    mergeSort(l,mid,a);
    mergeSort(mid+1,r,a);
    int x=l,y=mid+1,k=l;
    while (x<=mid || y<=r) {
        while (x<=mid && (y>r || a[x]<=a[y])) b[k++]=a[x++];
        while (y<=r && (x>mid || a[y]<=a[x])) b[k++]=a[y++];
    }
    for (int i = l; i <= r; ++i) {
        a[i]=b[i];
    }
}

int main(){
    scanf("%lld %lld",&n,&m);
    for (int i = 0; i < n*m; ++i) {
        scanf("%lld",&a[i]);
    }
    mergeSort(0,n*m-1,a);
    long long v,sum=0;
    double ans,level;
    scanf("%lld",&v);
    int i;
    for (i = 0; i < n*m; ++i) {
        sum+=a[i];
        level=double (v+sum)/(i+1);
        if (i+1==n*m || level<=a[i+1]) break;
    }
    printf("%.2lf\n%.2lf\n",level,double(i+1)*100/(n*m));
    return 0;
}