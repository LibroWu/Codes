//
// Created by Libro on 2021/5/10.
//

#include <iostream>

using namespace std;

const long long P1 = 10000019;
const long long key1 = 1031;
const long long P2 = 10000079;
const long long key2 = 10013;
const long long P3 = 10000121;
const long long key3 = 1093;

long long A[100005], B[100005], n, top = 0;
bool HASH1[P1 + 5] = {}, HASH2[P2 + 5] = {}, HASH3[P3 + 5] = {};

struct Pair {
    int a, b;

    Pair(int a, int b) : a(a), b(b) {}

    Pair() = default;
};

Pair p[1000005];

bool exist(long long x, long long y) {
    long long H1, H2, H3;
    H1 = (x * x % P1 + y * key1) % P1;
    H2 = (x * y % P2 + x * key2 + y * key3) % P2;
    H3 = (y * y * x % P1 + x * y * key1 + x) % P3;
    return (HASH1[H1] && HASH2[H2] && HASH3[H3]);
}

void Fill(long long x, long long y) {
    long long H1, H2, H3;
    H1 = (x * x % P1 + y * key1) % P1;
    H2 = (x * y % P2 + x * key2 + y * key3) % P2;
    H3 = (y * y * x % P1 + x * y * key1 + x) % P3;
    HASH1[H1] = true;
    HASH2[H2] = true;
    HASH3[H3] = true;
}

bool cmp(const Pair &a, const Pair &b) {
    return (A[a.a] + B[a.b] < A[b.a] + B[b.b]);
}

void push(const Pair &X) {
    p[++top] = X;
    int pos = top;
    while (pos > 1) {
        if (cmp(p[pos], p[pos >> 1])) swap(p[pos], p[pos >> 1]), pos >>= 1;
        else break;
    }
}

void pop() {
    p[1] = p[top--];
    int pos = 1, ptr;
    while ((pos << 1) <= top) {
        if (((pos << 1 | 1) > top) || cmp(p[pos << 1], p[pos << 1 | 1])) ptr = pos << 1;
        else ptr = pos << 1 | 1;
        if (cmp(p[ptr], p[pos])) swap(p[ptr], p[pos]), pos = ptr;
        else break;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];
    push(Pair(0, 0));
    for (int i = 0; i < n; ++i) {
        cout << A[p[1].a] + B[p[1].b] << ' ';
        if (!exist(p[1].a + 1, p[1].b)) {
            push(Pair(p[1].a + 1, p[1].b));
            Fill(p[1].a + 1, p[1].b);
        }
        if (!exist(p[1].a, p[1].b + 1)) {
            push(Pair(p[1].a, p[1].b + 1));
            Fill(p[1].a, p[1].b + 1);
        }
        pop();
    }
}