//
// Created by Libro on 2021/5/11.
//

#include <iostream>

using namespace std;
int n, a[1000005], b[1000005], c[1000005], d[1000005],num1[1000005],num2[1000005];
long long ans = 0;
constexpr long long P = 1e8 - 3;

void mergeSort(int l, int r, int *a) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid, a);
    mergeSort(mid + 1, r, a);
    int x = l, y = mid + 1, k = l;
    while (x <= mid && y <= r) {
        if (a[x] < a[y]) b[k++] = a[x++];
        else {
            b[k++] = a[y++];
            ans = (ans + mid - x + 1) % P;
        }
    }
    while (x <= mid) b[k++] = a[x++];
    while (y <= r) b[k++] = a[y++];
    for (int i = l; i <= r; ++i) {
        a[i] = b[i];
    }
}
void Sort(int l, int r, int *a,int *c) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    Sort(l, mid, a,c);
    Sort(mid + 1, r, a,c);
    int x = l, y = mid + 1, k = l;
    while (x <= mid && y <= r) {
        if (c[a[x]] < c[a[y]]) b[k++] = a[x++];
        else {
            b[k++] = a[y++];
        }
    }
    while (x <= mid) b[k++] = a[x++];
    while (y <= r) b[k++] = a[y++];
    for (int i = l; i <= r; ++i) {
        a[i] = b[i];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        num1[i]=i;
    }
    Sort(0,n-1,num1,c);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
        num2[i]=i;
    }
    Sort(0,n-1,num2,d);
    for (int i = 0; i < n; ++i) {
        a[num2[i]]=num1[i];
    }
    mergeSort(0,n-1,a);
    cout<<ans;
}