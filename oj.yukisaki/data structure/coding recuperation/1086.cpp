//
// Created by Libro on 2021/3/15.
//
#include <iostream>
#include <cstring>
using namespace std;

int n,h[1000005],v[1000005],ans[1000005],que[1000005],head,tail,Ans;

int main(){
    cin>>n;
    memset(ans,0,sizeof(ans));
    head=tail=0;
    for (int i = 0; i < n; ++i) {
        cin>>h[i]>>v[i];
        while (head<tail && h[que[tail-1]]<h[i]) {
            ans[i]+=v[que[tail-1]];
            --tail;
        }
        que[tail++]=i;
        if (head+1<tail && h[que[tail-2]]>h[que[tail-1]])
            ans[que[tail-2]]+=v[que[tail-1]];
    }
    Ans=0;
    for (int i = 0; i < n; ++i) {
        Ans=max(Ans,ans[i]);
    }
    cout<<Ans;
    return 0;
}