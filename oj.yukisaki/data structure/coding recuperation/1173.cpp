//
// Created by Libro on 2021/3/18.
//

#include <cstdio>
using namespace std;

long long n,a[1000005],b[1000005],c[100005];

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
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        scanf("%ld",&a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%ld",&c[i]);
    }
    mergeSort(0,n-1,a);
    mergeSort(0,n-1,c);
    long long ans1=0,ans2=0;
    for (int j = 0; j < n; ++j) {
        ans1+=a[j]*c[j];
        ans2+=a[j]*c[n-1-j];
    }
    printf("%ld %ld\n",ans1,ans2);
    return 0;
}