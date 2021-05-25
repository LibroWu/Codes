//
// Created by Libro on 2021/5/10.
//

#include <iostream>

using namespace std;

int parent[10005];

int getParent(int v){
    if (parent[v]==v) return v;
    return parent[v]= getParent(parent[v]);
}

int main(){
    int n,m,op,x,y;
    cin>>n>>m;
    for (int i = 0; i < n; ++i) parent[i]=i;
    for (int i = 0; i < m; ++i) {
        cin>>op>>x>>y;
        if (op==2) {
            cout<<((getParent(x)== getParent(y))?"Y\n":"N\n");
        } else {
            parent[getParent(x)]= getParent(y);
        }
    }
    return 0;
}