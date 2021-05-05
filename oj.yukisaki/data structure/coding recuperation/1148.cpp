//
// Created by Libro on 2021/4/26.
//

#include <iostream>
#include <string>

using namespace std;

const long long P1 = 1e9 + 7;
const long long key1 = 131;
const long long P2 = 1000000033;
const long long key2 = 113;
const long long P3 = 1000000093;
const long long key3 = 193;

char ch[1000005];
long long HASH1[1000005], HASH2[1000005], HASH3[1000005];
int st[200005], ed[200005], ptr_end = 1;
long long plus1[10005], plus2[10005], plus3[10005], n, m, T[12], Tn, op;
string s;

bool check(int x) {
    long long K1 = (HASH1[ed[T[0]]] - HASH1[ed[T[0]] - x] * plus1[x] % P1) % P1;
    if (K1 < 0) K1 += P1;
    //long long K2 = (HASH2[ed[T[0]]] - HASH2[ed[T[0]] - x] * plus2[x] % P2) % P2;
    //if (K2 < 0) K2 += P2;
    //long long K3 = (HASH3[ed[T[0]]] - HASH3[ed[T[0]] - x] * plus3[x] % P3) % P3;
    //if (K3 < 0) K3 += P3;
    for (int i = 1; i < Tn; ++i) {
        long long k1 = (HASH1[ed[T[i]]] - HASH1[ed[T[i]] - x] * plus1[x] % P1) % P1;
        if (k1 < 0) k1 += P1;
        if (K1 != k1) return false;
        //long long k2 = (HASH2[ed[T[i]]] - HASH2[ed[T[i]] - x] * plus2[x] % P2) % P2;
        //if (k2 < 0) k2 += P2;
        //if (K2 != k2) return false;
        //long long k3 = (HASH3[ed[T[i]]] - HASH3[ed[T[i]] - x] * plus3[x] % P3) % P3;
        //if (k3 < 0) k3 += P3;
        //if (K3 != k3) return false;
    }
    return true;
}

int main() {
    plus1[0] = plus2[0] = plus3[0] = 1;
    for (int i = 1; i <= 10001; ++i) {
        plus1[i] = plus1[i - 1] * key1 % P1;
        //plus2[i] = plus2[i - 1] * key2 % P2;
        //plus3[i] = plus3[i - 1] * key3 % P3;
    }
    HASH1[0] = HASH2[0] =HASH3[0]= 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        int len = s.length();
        for (int j = 0; j < len; ++j) {
            HASH1[ptr_end + j] = (HASH1[ptr_end + j - 1] * key1 + s[j]) % P1;
            //HASH2[ptr_end + j] = (HASH2[ptr_end + j - 1] * key2 + s[j]) % P2;
            //HASH3[ptr_end + j] = (HASH3[ptr_end + j - 1] * key3 + s[j]) % P3;
        }
        st[i] = ptr_end;
        ed[i] = ptr_end = ptr_end + len;
        --ed[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> s;
            int len = s.length();
            for (int j = 0; j < len; ++j) {
                HASH1[ptr_end + j] = (HASH1[ptr_end + j - 1] * key1 + s[j]) % P1;
                //HASH2[ptr_end + j] = (HASH2[ptr_end + j - 1] * key2 + s[j]) % P2;
                //HASH3[ptr_end + j] = (HASH3[ptr_end + j - 1] * key3 + s[j]) % P3;
            }
            st[++n] = ptr_end;
            ed[n] = ptr_end = ptr_end + len;
            --ed[n];
        } else {
            cin >> Tn;
            int s_len = 100000;
            for (int j = 0; j < Tn; ++j) {
                cin >> T[j];
                s_len = min(s_len, ed[T[j]] - st[T[j]] + 1);
            }
            int l = 0, r = s_len, mid, K;
            while (l < r) {
                mid = (l + r + 1) >> 1;
                if (check(mid)) l = mid;
                else r = mid - 1;
            }
            cout << l << '\n';
        }
    }
}