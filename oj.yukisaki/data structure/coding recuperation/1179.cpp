//
// Created by Libro on 2021/5/10.
//
#include <iostream>

using namespace std;

int n, m, r;

struct Mouse {
    long long P, S, num;
} mice[2000005], b[2000005];

void mergeSort(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    int x = l, y = mid + 1, k = l;
    while (x <= mid && y <= r) {
        if (mice[x].S > mice[y].S || mice[x].S == mice[y].S && mice[x].num <= mice[y].num)
            b[k++] = mice[x++];
        else
            b[k++] = mice[y++];
    }
    while (x <= mid) b[k++] = mice[x++];
    while (y <= r) b[k++] = mice[y++];
    for (int i = l; i <= r; ++i) {
        mice[i] = b[i];
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin >> n >> r;
    n <<= 1;
    for (int i = 0; i < n; ++i) {
        cin >> mice[i].S;
    }
    for (int i = 0; i < n; ++i) {
        cin >> mice[i].P;
        mice[i].num = i + 1;
    }
    for (int i = 0; i < r; ++i) {
        mergeSort(0, n - 1);
        for (int j = 0; j < n; j += 2) {
            if (mice[j].P > mice[j + 1].P) mice[j].S += 2;
            else if (mice[j].P < mice[j + 1].P) mice[j + 1].S += 2;
            else ++mice[j].S, ++mice[j + 1].S;
        }
    }
    mergeSort(0, n - 1);
    for (int i = 0; i < n; ++i) cout << mice[i].num << ' ';
    return 0;
}