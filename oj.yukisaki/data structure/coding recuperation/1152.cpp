#include<iostream>
#include<string>
using namespace std;
int dp[205][205]={};

bool is_pair(char a,char b){
    if (a=='(' && b==')') return true;
    if (a=='[' && b==']') return true;
    if (a=='{' && b=='}') return true;
    return false;
}

int main(){
    string s;
    cin>>s;
    int len=s.length();
    for (int i=2;i<len;++i){
        for (int j=0;j<len-i;++j)
            for (int k = j; k < j+len; ++k)
                if (is_pair(s[j],s[k])) dp[j][k]= max(dp[j][k],dp[j+1][k-1]+2);
                else dp[j][k]= max(dp[j][k],dp[j+1][k-1]);
    }
    cout<<dp[0][len-1];
}