//stack and hash
#include <iostream>
#define MAXN 1000005
using namespace std;

const int key1 = 13;
const int key2 = 23;
const int key3 = 17;
const int p1 = 200003;
const int p2 = 200009;
const int p3 = 2000381;
int cnt, s2_hash1, s2_hash2, s2_hash3, lens, lent;
char st[MAXN], c, s[MAXN], t[MAXN];
long long HASH_1[MAXN], HASH_2[MAXN], HASH_3[MAXN];
int main() {
    s2_hash1 = s2_hash2 = 0;
    lens = lent = 0;
    while (1) {
        c = getchar();
        if (c == ' ') continue;
        if (c == '\n' || c == EOF) break;
        s[lens++] = c;
    }
    s[lens] = '\0';
    while (1) {
        c = getchar();
        if (c == ' ') continue;
        if (c == '\n' || c == EOF) break;
        t[lent++] = c;
    }
    t[lent] = '\0';
    int carry1 = 1, carry2 = 1, carry3 = 1;
    for (int i = 0; i < lent; ++i) {
        carry1 = carry1 * key1 % p1;
        carry2 = carry2 * key2 % p2;
        carry3 = carry3 * key3 % p3;
        s2_hash1 = (s2_hash1 * key1 + t[i]) % p1;
        s2_hash2 = (s2_hash2 * key2 + t[i]) % p2;
        s2_hash3 = (s2_hash3 * key3 + t[i]) % p3;
    }
    HASH_1[0] = HASH_2[0] = HASH_3[0] = 0;
    for (int i = 0; i < lens; ++i) {
        st[++cnt] = s[i];
        HASH_1[cnt] = (HASH_1[cnt - 1] * key1 + s[i]) % p1;
        HASH_2[cnt] = (HASH_2[cnt - 1] * key2 + s[i]) % p2;
        HASH_3[cnt] = (HASH_3[cnt - 1] * key3 + s[i]) % p3;
        if (cnt >= lent) {
            int check1 = (HASH_1[cnt] - HASH_1[cnt - lent] * carry1 % p1) % p1;
            if (check1 < 0) check1 += p1;
            int check2 = (HASH_2[cnt] - HASH_2[cnt - lent] * carry2 % p2) % p2;
            if (check2 < 0) check2 += p2;
            int check3 = (HASH_3[cnt] - HASH_3[cnt - lent] * carry3 % p3) % p3;
            if (check3 < 0) check3 += p3;
            if (check1 == s2_hash1 && check2 == s2_hash2 && check3 == s2_hash3)
                cnt -= lent;
        }
    }
    for (int i = 1; i <= cnt; ++i) cout << st[i];
    cout << '\n';
    return 0;
}