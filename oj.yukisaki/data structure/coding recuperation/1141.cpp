//
// Created by Libro on 2021/4/29.
//

#include <iostream>
#include <string>

using namespace std;

int n;
string s;

const long long P1 = 10000019;
const long long key1 = 131;
const long long P2 = 10000079;
const long long key2 = 113;
const long long P3 = 10000121;
const long long key3 = 193;

bool p1[P1 + 5] = {0}, p2[P2 + 5] = {0}, p3[P3 + 5] = {0};
long long HASH1, HASH2, HASH3, ans = 0;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int len = s.length();
        HASH1 = HASH2 = HASH3 = 0;
        for (int j = 0; j < len; ++j) {
            HASH1 = (HASH1 * key1 + s[j]) % P1;
            HASH2 = (HASH2 * key2 + s[j]) % P2;
            HASH3 = (HASH3 * key3 + s[j]) % P3;
        }
        if (p1[HASH1] && p2[HASH2] && p3[HASH3]) ++ans;
        p1[HASH1] = p2[HASH2] = p3[HASH3] = 1;
    }
    cout << n -ans;
}