//
// Created by Libro on 2021/5/10.
//

#include <iostream>
#include <cstring>

using namespace std;

long long n, k, a[100005], l, r, mid, b[100005], c[100005], d[100005], f[100005], t[100005];

void mergeSort(int l, int r, long long *a, long long *b) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid, a, b);
    mergeSort(mid + 1, r, a, b);
    int x = l, y = mid + 1, k = l;
    while (x <= mid && y <= r) {
        if (f[a[x]] < f[a[y]])
            b[k++] = a[x++];
        else
            b[k++] = a[y++];
    }
    while (x <= mid) b[k++] = a[x++];
    while (y <= r) b[k++] = a[y++];
    for (int i = l; i <= r; ++i) a[i] = b[i];
}

inline int lowbit(int x) {
    return (x & -x);
}

void add(int x) {
    while (x <= n + 1) {
        t[x] += 1;
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        res += t[x];
        x -= lowbit(x);
    }
    return res;
}

bool check(long long x) {
    long long count = 0;
    memset(t,0,sizeof(t));
    for (int i = 0; i <=n; ++i) {
        f[i]=a[i]-i*x;
        c[i]=i;
    }
    mergeSort(0,n,c,b);
    int cnt=1;
    for (int i = 0; i <= n; ++i) {
        if (i && f[c[i]]==f[c[i-1]]) d[c[i]]=cnt;
        else d[c[i]]=cnt++;
    }
    for (int i = 0; i <= n; ++i) {
        count+= query(d[i]);
        add(d[i]);
    }
    return (count>=k);
}

int main() {
    cin >> n >> k;
    a[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i]*=100000;
        a[i] += a[i - 1];
    }
    l = 0, r = 10000000000;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%.3f",double (l)/100000);
}
