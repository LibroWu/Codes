//记忆化，正则表达式
#include <iostream>
#include <cstring>
using namespace std;

int t;
string s;
int ele[205][205],subL[205][205];
bool Set(int, int);

bool subElement(char ch) {
    if (ch == '{' || ch == '}' || ch == ',') return true;
    return false;
}

bool element(int l, int r) {
    if (l > r) return false;
    if (ele[l][r]!=0) {
        return (ele[l][r]==1);
    }
    if (l == r) {
        if (subElement(s[l]))
            ele[l][r] = 1;
        else ele[l][r]=-1;
        return (ele[l][r]==1);
    }
    if (Set(l, r)) ele[l][r]=1;
    else ele[l][r]=-1;
    return (ele[l][r]==1);
}

bool subList(int l, int r) {
    if (l > r) return false;
    if (subL[l][r]!=0)
        return (subL[l][r]==1);
    if (element(l, r)) {
        subL[l][r]=1;
        return true;
    }
    for (int i = l; i <= r; ++i)
        if (s[i] == ',') {
            if (element(l, i - 1) && subList(i + 1, r)) {
                subL[l][r]=1;
                return true;
            }
        }
    subL[l][r]=-1;
    return false;
}

bool List(int l, int r) {
    if (l > r) return true;
    return subList(l, r);
}

bool Set(int l, int r) {
    if (s[l] == '{' && s[r] == '}') return List(l + 1, r - 1);
    else return false;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin>>s;
        memset(ele,0,sizeof(ele));
        memset(subL,0,sizeof(subL));
        if (Set(0, s.length() - 1))
            cout << "Word #" << i << ": Set\n";
        else
            cout << "Word #" << i << ": No Set\n";
    }
}