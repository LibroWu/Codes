#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N=200005;
int n,st[N],top=0;
long long a[N],sum[N],ANS=0;

int main(){
    cin>>n;
    sum[0]=a[0]=0;
    for (int i = 1; i <= n; ++i) {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    for (int i = 0; i <= n; ++i) {
        while (top && a[st[top-1]]>=a[i]) {
            ANS=max(ANS,(sum[i-1]-sum[st[top-2]])*a[st[top-1]]);
            --top;
        }
        st[top++]=i;
    }
    for (int j = 1; j < top; ++j)
        ANS=max(ANS,(sum[n]-sum[st[j-1]])*a[st[j]]);
    cout<<ANS;
    return 0;
}