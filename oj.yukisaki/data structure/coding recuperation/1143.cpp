//
// Created by Libro on 2021/4/27.
//

#include <iostream>
#include <cstring>

using namespace std;

int n, x[15005], y[15005], num[15005], b[15005], p[32005], ans[15005],count[15005];

void mergeSort(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid || j <= r) {
        while (i <= mid && (j > r || x[num[i]] < x[num[j]] || (x[num[i]] == x[num[j]] && y[num[i]] <= y[num[j]])))
            b[k++] = num[i++];
        while (j <= r && (i > mid || x[num[i]] > x[num[j]] || (x[num[i]] == x[num[j]] && y[num[i]] >= y[num[j]])))
            b[k++] = num[j++];
    }
    for (int ii = l; ii <= r; ++ii) num[ii] = b[ii];
}

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int k) {
    while (x <= 32000) {
        p[x] += k;
        x += lowbit(x);
    }
}

int query(int x) {
    int tmp = 0;
    while (x) {
        tmp += p[x];
        x -= lowbit(x);
    }
    return tmp;
}

int main() {
    memset(p, 0, sizeof(p));
    memset(ans, 0, sizeof(ans));
    memset(count, 0, sizeof(count));
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d",&x[i],&y[i]);
        ++x[i];
        ++y[i];
        num[i] = i;
    }
    mergeSort(1, n);
    int N=0;
    for (int i = 1; i <= n ; ++i) {
        if (x[num[i]]==x[num[N]] && y[num[i]]==y[num[N]]) ++count[N];
        else {
            count[++N]=1;
            num[N]=num[i];
        }
    }
    int pre = 1;
    for (int i = 1; i <= N; ++i) {
        ans[query(y[num[i]])]+=count[i];
        add(y[num[i]], count[i]);
    }
    for (int i = 0; i < n; ++i) printf("%d\n",ans[i]);
}