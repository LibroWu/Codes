//
// Created by Libro on 2021/5/11.
//

#include <iostream>

using namespace std;
using namespace std;

long long n, m, a[1000005], b[1000005], c[1000005], t[1000005], l[100005], s[1000005], m1 = 0, m2 = 0;
double ans1 = 0, ans2 = 0;

void mergeSort(int l, int r) {
    if (l == r) return;
    int mid = l + r >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    int x = l, y = mid + 1, k = l;
    while (x <= mid || y <= r) {
        while (x <= mid && (y > r || t[a[x]] <= t[a[y]])) b[k++] = a[x++];
        while (y <= r && (x > mid || t[a[y]] <= t[a[x]])) b[k++] = a[y++];
    }
    for (int i = l; i <= r; ++i) {
        a[i] = b[i];
    }
}

int main() {
    int n, m;
    cin >> n;
    l[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i];
        l[i]+=l[i-1];
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s[i] >> t[i];
        a[i] = i;
    }
    mergeSort(0, m - 1);
    for (int i = 0; i < m; ++i)
        if (s[a[i]] == 1) b[m1++] = a[i];
        else c[m2++] = a[i];
    int ptr1 = 0, ptr2 = 0;
    int i;
    for (i = 0; i < n-1; ++i) {
        int tmp1=ptr1,tmp2=ptr2;
        while (tmp1<m1 && t[b[tmp1]]<=l[i]) ++tmp1;
        while (tmp2<m2 && t[c[tmp2]]<=l[i]) ++tmp2;
        int tmp= min(tmp1,tmp2);
        while (ptr1<tmp) ans1+=l[i]-t[b[ptr1++]];
        while (ptr2<tmp) ans2+=l[i]-t[c[ptr2++]];
    }
    while (ptr1<m1) ans1+=l[i]-t[b[ptr1++]];
    while (ptr2<m2) ans2+=l[i]-t[c[ptr2++]];
    printf("%.2lf %.2lf",ans1/m1,ans2/m2);
}