//
// Created by Libro on 2021/3/18.
//

#include <cstdio>
using namespace std;

int n,a[1000005],b[1000005];

void mergeSort(int l,int r) {
    if (l==r) return;
    int mid=l+r>>1;
    mergeSort(l,mid);
    mergeSort(mid+1,r);
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
        scanf("%d",&a[i]);
    }
    mergeSort(0,n-1);
    for (int j = 0; j < n; ++j) {
        printf("%d ",a[j]);
    }
}