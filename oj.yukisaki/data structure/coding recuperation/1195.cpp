//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>

using namespace std;
const long long MAXN = 1000000000;
const int MoveX[4] = {1, -1, 0, 0};
const int MoveY[4] = {0, 0, 1, -1};
long long a[105][105], t, dist[105][105][3];
bool in_que[105][105][3];
int n, m, l, r;

struct tup {
    int x, y, k;
} que[1000000];

int main() {
    memset(in_que, 0, sizeof(in_que));
    cin >> n >> t;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            for (int k = 0; k < 3; ++k) {
                dist[i][j][k] = MAXN;
            }
        }
    dist[1][1][0] = 0;
    l = r = 0;
    que[r].x = 1, que[r].y = 1, que[r].k = 0;
    ++r;
    while (l < r) {
        tup u = que[l++];
        in_que[u.x][u.y][u.k] = false;
        for (int i = 0; i < 4; ++i) {
            int x = u.x + MoveX[i];
            int y = u.y + MoveY[i];
            int k = (u.k + 1) % 3;
            if (x >= 1 && x <= n && y >= 1 && y <= n) {
                int cost = ((k == 0) ? a[x][y]+t : t);
                if (dist[u.x][u.y][u.k]+cost<dist[x][y][k]) {
                    dist[x][y][k]=dist[u.x][u.y][u.k]+cost;
                    if (!in_que[x][y][k]) {
                        in_que[x][y][k]=true;
                        que[r].x=x,que[r].y=y,que[r].k=k;
                        ++r;
                    }
                }
            }
        }
    }
    int ans=min(min(dist[n][n][0],dist[n][n][1]),dist[n][n][2]);
    cout<<((ans==MAXN)?-1:ans);
}