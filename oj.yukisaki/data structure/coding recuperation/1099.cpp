//
// Created by Libro on 2021/3/18.
//
#include <iostream>

using namespace std;

int n,a[4005],head,tail,que[4005],f[4005],ans;

int get(int j){
    int l=0,r=tail-1,mid;
    while (l<r) {
        mid=l+r>>1;
        if (a[que[mid]]<a[j]) l=mid+1;
        else r=mid;
    }
    return l;
}

int main() {
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
        a[n+i]=a[i];
    }
    for (int i = 0; i < n; ++i) {
        head=tail=0;
        for (int j = i; j < i+n; ++j) {
            if (tail==0 || a[j]>a[que[tail-1]]) que[tail++]=j;
            else que[get(j)]=j;
        }
        ans=max(ans,tail);
    }
    cout<<n-ans;
};