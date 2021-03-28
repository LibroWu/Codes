//
// Created by Libro on 2021/3/20.
//

#include <iostream>

#define LL long long
using namespace std;
const LL INF = 100000000000000;
LL T, MaxP, W, DP1[2005][2005], DP0[2005][2005], AP, BP, AS, BS, tmp[2005], que[2005], head, tail;

int main() {
    cin >> T >> MaxP >> W;
    for (int i = 0; i <= T + 1; ++i) {
        for (int j = 0; j <= MaxP + 1; ++j) {
            DP1[i][j] = DP0[i][j] = -INF;
        }
    }
    DP0[0][0] = DP1[0][0] = tmp[0] = 0;
    for (int i = 1; i <= MaxP + 1; ++i) {
        tmp[i] = -INF;
    }
    LL ans = -INF;
    for (int i = 1; i <= T; ++i) {
        cin >> AP >> BP >> AS >> BS;
        head = tail = 0;
        for (int j = 0; j <= MaxP; ++j) {
            DP0[i][j]=max(DP0[i][j],tmp[j]);
        }
        for (int j = 0; j <= MaxP; ++j) {
            while (head < tail && tmp[que[tail - 1]] + que[tail - 1] * AP <= tmp[j] + j * AP) --tail;
            while (head < tail && que[head] + AS < j) ++head;
            que[tail++] = j;
            DP1[i][j] = max(DP1[i][j], tmp[que[head]] + que[head] * AP - j * AP);
        }
        head = tail = 0;
        for (int j = MaxP; j >= 0; --j) {
            while (head < tail && tmp[que[tail - 1]] + que[tail - 1] * BP <= tmp[j] + j * BP) --tail;
            while (head < tail && que[head] > j + BS) ++head;
            que[tail++] = j;
            DP1[i][j] = max(DP1[i][j], tmp[que[head]] + que[head] * BP - j * BP);
            ans = max(DP1[i][j], ans);
        }
        if (i > W)
            for (int j = 0; j <= MaxP; ++j) {
                tmp[j] = max(tmp[j], DP1[i - W][j]);
            }
        for (int j = 0; j < ; ++j) {

        }
    }
    cout << ans << endl;
}