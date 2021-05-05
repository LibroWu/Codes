//
// Created by Libro on 2021/4/26.
//

#include <iostream>

using namespace std;

long long n,m,a[105],ptr[105],ans[100005];

int main(){
    cin>>n>>m;
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
        ptr[i]=0;
    }
    ans[0]=1;
    for (int i = 1; i <= m; ++i) {
        long long k,M=100000000000000000;
        for (int j = 0; j < n; ++j) {
            if (ans[ptr[j]]*a[j]<M) {
                M=ans[ptr[j]]*a[j];
                k=j;
            }
        }
        if (M<=ans[i-1]) {
            ++ptr[k];
            --i;
        }
        else ans[i]=ans[ptr[k]++]*a[k];
    }
    cout<<ans[m];
}