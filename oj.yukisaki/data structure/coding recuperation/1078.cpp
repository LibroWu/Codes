#include <iostream>

using namespace std;

int n,p,v,len=0,V[10000005];

int main(){
    cin>>n;
    for (int i=0;i<n;++i){
        cin>>p>>v;
        if (!len){
            V[len++]=v;
        }
        else{
            while (len&&V[len-1]>v) --len;
            V[len++]=v;
        }
    }
    cout<<len<<'\n';
}