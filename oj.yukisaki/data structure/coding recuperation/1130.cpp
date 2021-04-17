//
// Created by Libro on 2021/4/12.
//

#include <iostream>
using namespace std;
long long n,m,que[30005],ptr1,ptr2,top=0,subtop;
char st[1000005],s[1000];

void divide(long long t) {
    subtop=0;
    while (t) {
        s[subtop++]=t%10+'0';
        t=t/10;
    }
    while (subtop) {
        while (top && m && st[top-1]<s[subtop-1]) {
            --top;
            --m;
        }
        st[top++]=s[--subtop];
    }
}

int main(){
    cin>>n>>m;
    que[0]=1;
    ptr1=ptr2=0;
    divide(que[0]);
    for (int i = 1; i < n; ++i) {
        while (que[ptr1]*2+1<=que[i-1]) ++ptr1;
        while (que[ptr2]*4+5<=que[i-1]) ++ptr2;
        if (que[ptr1]*2+1<que[ptr2]*4+5)
            que[i]=que[ptr1++]*2+1;
        else que[i]=que[ptr2++]*4+5;
        divide(que[i]);
    }
    for (int i = 0; i < n; ++i) cout<<que[i];
    cout<<'\n';
    for (int i = 0; i < top-m; ++i) cout<<st[i];
}