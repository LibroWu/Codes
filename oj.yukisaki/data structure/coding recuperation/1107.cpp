//
// Created by Libro on 2021/3/29.
//

#include <iostream>
#include <cstring>

using namespace std;

bool t[2000000];
int d,n,M,ans=0;

int main(){
    memset(t,0,sizeof(t));
    cin>>d>>n;
    M=(1<<(d-1))-1;
    for (int i = 0; i < n; ++i) {
        int p=1;
        while (p<=M) {
            t[p]^=1;
            if (t[p])p=p<<1;
            else p=(p<<1)+1;
        }
        ans=p;
    }
    cout<<ans;
}