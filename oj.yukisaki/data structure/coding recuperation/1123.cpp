//
// Created by Libro on 2021/4/12.
//

#include <iostream>

using namespace std;

int n,v[1024],l,ans;

int battle(int l,int r){
    if (r-l==1)
        return ((v[l]>v[r])?l:r);
    int mid=(l+r)>>1;
    int ll= battle(l,mid),rr= battle(mid+1,r);
    if (v[ll]>v[rr]) {
        ans=rr;
        return ll;
    } else {
        ans=ll;
        return rr;
    }
}

int main(){
    cin>>n;
    l=1<<n;
    for (int i = 1; i <= l; ++i) {
        cin>>v[i];
    }
    battle(1,l);
    cout<<ans;
}